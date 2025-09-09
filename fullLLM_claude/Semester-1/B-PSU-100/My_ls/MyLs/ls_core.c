#include "my_ls.h"

static char *build_path(char const *dir, char const *name)
{
    int dir_len = my_strlen(dir);
    int name_len = my_strlen(name);
    char *path = malloc(dir_len + name_len + 2);
    
    if (!path)
        return 0;
    
    my_strcpy(path, dir);
    if (dir_len > 0 && dir[dir_len - 1] != '/')
        my_strcat(path, "/");
    my_strcat(path, name);
    
    return path;
}

static int should_show_file(char const *name, options_t options)
{
    if (options.all)
        return 1;
    
    return name[0] != '.';
}

static file_info_t *read_directory_entries(char const *path, options_t options, int *count)
{
    DIR *dir;
    struct dirent *entry;
    file_info_t *files;
    int capacity = 1000;
    char *full_path;
    
    *count = 0;
    
    dir = opendir(path);
    if (!dir) {
        write(2, path, my_strlen(path));
        write(2, ": ", 2);
        write(2, strerror(errno), my_strlen(strerror(errno)));
        write(2, "\n", 1);
        return 0;
    }
    
    files = malloc(capacity * sizeof(file_info_t));
    if (!files) {
        closedir(dir);
        return 0;
    }
    
    while ((entry = readdir(dir)) != 0) {
        if (!should_show_file(entry->d_name, options))
            continue;
            
        if (*count >= capacity) {
            break;
        }
        
        files[*count].name = my_strdup(entry->d_name);
        files[*count].path = build_path(path, entry->d_name);
        
        full_path = files[*count].path;
        if (lstat(full_path, &files[*count].stat) == -1) {
            write(2, full_path, my_strlen(full_path));
            write(2, ": ", 2);
            write(2, strerror(errno), my_strlen(strerror(errno)));
            write(2, "\n", 1);
            free(files[*count].name);
            free(files[*count].path);
            continue;
        }
        
        (*count)++;
    }
    
    closedir(dir);
    return files;
}

int list_directory(char const *path, options_t options)
{
    file_info_t *files;
    int count;
    int i;
    
    files = read_directory_entries(path, options, &count);
    if (!files)
        return 84;
    
    sort_files(files, count, options);
    
    if (options.long_format) {
        my_putstr("total ");
        my_put_nbr(0);
        my_putchar('\n');
    }
    
    for (i = 0; i < count; i++) {
        if (options.long_format) {
            print_long_format(&files[i]);
        } else {
            my_putstr(files[i].name);
            my_putchar('\n');
        }
        
        if (options.recursive && S_ISDIR(files[i].stat.st_mode) &&
            my_strcmp(files[i].name, ".") != 0 && my_strcmp(files[i].name, "..") != 0) {
            my_putchar('\n');
            my_putstr(files[i].path);
            my_putstr(":\n");
            list_directory(files[i].path, options);
        }
    }
    
    free_file_info(files, count);
    return 0;
}

int list_file(char const *path, options_t options)
{
    file_info_t file;
    struct stat st;
    
    if (lstat(path, &st) == -1) {
        write(2, path, my_strlen(path));
        write(2, ": ", 2);
        write(2, strerror(errno), my_strlen(strerror(errno)));
        write(2, "\n", 1);
        return 84;
    }
    
    if (S_ISDIR(st.st_mode) && !options.directory) {
        return list_directory(path, options);
    }
    
    file.name = my_strdup(path);
    file.path = my_strdup(path);
    file.stat = st;
    
    if (options.long_format) {
        print_long_format(&file);
    } else {
        my_putstr(file.name);
        my_putchar('\n');
    }
    
    free(file.name);
    free(file.path);
    
    return 0;
}
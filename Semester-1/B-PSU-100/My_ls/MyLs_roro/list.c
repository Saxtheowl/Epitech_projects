#include "my_ls.h"

static char *build_path(char *dir, char *name)
{
    char *path;
    int dir_len = my_strlen(dir);
    int name_len = my_strlen(name);
    int i, j;
    
    path = malloc(dir_len + name_len + 2);
    if (!path)
        return NULL;
    
    for (i = 0; i < dir_len; i++)
        path[i] = dir[i];
    
    if (dir_len > 0 && dir[dir_len - 1] != '/') {
        path[i] = '/';
        i++;
    }
    
    for (j = 0; j < name_len; j++, i++)
        path[i] = name[j];
    
    path[i] = '\0';
    return path;
}

static void print_total(file_info_t *list)
{
    long total = 0;
    file_info_t *current = list;
    
    while (current) {
        total += current->st.st_blocks;
        current = current->next;
    }
    my_putstr("total ");
    print_number(total / 2);
    my_putchar('\n');
}

int list_directory(char *path, options_t *opts)
{
    DIR *dir;
    struct dirent *entry;
    file_info_t *file_list = NULL;
    file_info_t *new_file;
    char *full_path;
    
    dir = opendir(path);
    if (!dir) {
        perror("my_ls");
        return 84;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        if (!(opts->flags & OPT_ALL) && entry->d_name[0] == '.')
            continue;
        
        full_path = build_path(path, entry->d_name);
        if (!full_path) {
            closedir(dir);
            free_file_list(file_list);
            return 84;
        }
        
        new_file = create_file_info(entry->d_name, full_path);
        free(full_path);
        if (new_file)
            file_list = add_file_to_list(file_list, new_file);
    }
    closedir(dir);
    
    file_list = sort_files(file_list, opts);
    
    if (opts->flags & OPT_LONG)
        print_total(file_list);
    
    if (opts->flags & OPT_LONG) {
        file_info_t *current = file_list;
        while (current) {
            print_long_format(current);
            current = current->next;
        }
    } else {
        print_simple_format(file_list, opts);
    }
    
    if (opts->flags & OPT_RECUR) {
        file_info_t *current = file_list;
        while (current) {
            if (S_ISDIR(current->st.st_mode) && 
                my_strcmp(current->name, ".") != 0 && 
                my_strcmp(current->name, "..") != 0) {
                my_putchar('\n');
                my_putstr(current->path);
                my_putstr(":\n");
                list_directory(current->path, opts);
            }
            current = current->next;
        }
    }
    
    free_file_list(file_list);
    return 0;
}

int list_file(char *path, options_t *opts)
{
    file_info_t *file;
    char *name;
    int i;
    
    name = path;
    for (i = 0; path[i]; i++) {
        if (path[i] == '/')
            name = &path[i + 1];
    }
    
    file = create_file_info(name, path);
    if (!file) {
        perror("my_ls");
        return 84;
    }
    
    if (opts->flags & OPT_LONG) {
        print_long_format(file);
    } else {
        my_putstr(file->name);
        my_putchar('\n');
    }
    
    free_file_list(file);
    return 0;
}
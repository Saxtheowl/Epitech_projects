/*
** EPITECH PROJECT, 2024
** Tree
** File description:
** Tree directory listing implementation
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_PATH 4096

typedef struct {
    int show_all;        // -a
    int dirs_only;       // -d  
    int max_level;       // -L
    int full_path;       // -f
    int has_level_limit;
} options_t;

typedef struct {
    int dirs;
    int files;
} count_t;

void my_write(char *str)
{
    int len = 0;
    while (str[len])
        len++;
    write(1, str, len);
}

void print_usage(void)
{
    my_write("usage: tree [-adf] [-L level] [directory ...]\n");
}

int my_strcmp(char *s1, char *s2)
{
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}

int my_strlen(char *str)
{
    int len = 0;
    while (str[len])
        len++;
    return len;
}

int my_atoi(char *str)
{
    int result = 0;
    int i = 0;
    
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

void my_itoa(int num, char *str)
{
    int i = 0;
    int temp = num;
    
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    
    // Count digits
    while (temp > 0) {
        i++;
        temp /= 10;
    }
    
    str[i] = '\0';
    i--;
    
    while (num > 0) {
        str[i] = (num % 10) + '0';
        num /= 10;
        i--;
    }
}

char *my_strcat(char *dest, char *src)
{
    int i = 0;
    int dest_len = my_strlen(dest);
    
    while (src[i]) {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return dest;
}

char *my_strcpy(char *dest, char *src)
{
    int i = 0;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int is_hidden(char *name)
{
    return (name[0] == '.' && my_strcmp(name, ".") != 0 && my_strcmp(name, "..") != 0);
}

void print_indent(int level, int *is_last, int is_last_current)
{
    int i;
    
    for (i = 0; i < level; i++) {
        if (i == level - 1) {
            if (is_last_current)
                my_write("`-- ");
            else
                my_write("|-- ");
        } else {
            if (is_last[i])
                my_write("    ");
            else
                my_write("|   ");
        }
    }
}

void sort_entries(struct dirent **entries, int count)
{
    int i, j;
    struct dirent *temp;
    
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (my_strcmp(entries[j]->d_name, entries[j + 1]->d_name) > 0) {
                temp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = temp;
            }
        }
    }
}

void print_tree(char *path, options_t *opts, int level, int *is_last, count_t *count)
{
    DIR *dir;
    struct dirent *entry;
    struct dirent **entries = NULL;
    int entry_count = 0;
    int capacity = 100;
    struct stat st;
    char full_path[MAX_PATH];
    int i;
    
    if (opts->has_level_limit && level >= opts->max_level)
        return;
    
    dir = opendir(path);
    if (!dir)
        return;
    
    entries = malloc(sizeof(struct dirent*) * capacity);
    if (!entries) {
        closedir(dir);
        return;
    }
    
    // Collect entries
    while ((entry = readdir(dir)) != NULL) {
        if (my_strcmp(entry->d_name, ".") == 0 || my_strcmp(entry->d_name, "..") == 0)
            continue;
            
        if (!opts->show_all && is_hidden(entry->d_name))
            continue;
            
        if (entry_count >= capacity)
            break;
        
        entries[entry_count] = malloc(sizeof(struct dirent));
        if (entries[entry_count]) {
            *entries[entry_count] = *entry;
            entry_count++;
        }
    }
    closedir(dir);
    
    // Sort entries
    sort_entries(entries, entry_count);
    
    // Print entries
    for (i = 0; i < entry_count; i++) {
        int path_len = 0;
        int name_len = 0;
        
        // Build full path
        while (path[path_len])
            path_len++;
        while (entries[i]->d_name[name_len])
            name_len++;
            
        if (path_len + name_len + 2 >= MAX_PATH)
            continue;
            
        my_strcpy(full_path, path);
        if (path[path_len - 1] != '/') {
            full_path[path_len] = '/';
            full_path[path_len + 1] = '\0';
        }
        my_strcat(full_path, entries[i]->d_name);
        
        if (stat(full_path, &st) != 0)
            continue;
            
        int is_dir = S_ISDIR(st.st_mode);
        
        if (opts->dirs_only && !is_dir)
            continue;
            
        // Print indentation
        if (level > 0)
            print_indent(level, is_last, i == entry_count - 1);
            
        // Print name or full path
        if (opts->full_path) {
            my_write(full_path);
        } else {
            my_write(entries[i]->d_name);
        }
        my_write("\n");
        
        // Update counters
        if (is_dir)
            count->dirs++;
        else
            count->files++;
            
        // Recurse into directories
        if (is_dir) {
            is_last[level] = (i == entry_count - 1);
            print_tree(full_path, opts, level + 1, is_last, count);
        }
    }
    
    // Free entries
    for (i = 0; i < entry_count; i++) {
        free(entries[i]);
    }
    free(entries);
}

int parse_args(int argc, char **argv, options_t *opts, char **directory)
{
    int i;
    
    opts->show_all = 0;
    opts->dirs_only = 0;
    opts->max_level = 0;
    opts->full_path = 0;
    opts->has_level_limit = 0;
    *directory = ".";
    
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            int j;
            for (j = 1; argv[i][j]; j++) {
                switch (argv[i][j]) {
                    case 'a':
                        opts->show_all = 1;
                        break;
                    case 'd':
                        opts->dirs_only = 1;
                        break;
                    case 'f':
                        opts->full_path = 1;
                        break;
                    case 'L':
                        if (j + 1 < my_strlen(argv[i])) {
                            // -L3 format
                            opts->max_level = my_atoi(&argv[i][j + 1]);
                            opts->has_level_limit = 1;
                            goto next_arg;
                        } else if (i + 1 < argc) {
                            // -L 3 format
                            opts->max_level = my_atoi(argv[i + 1]);
                            opts->has_level_limit = 1;
                            i++;
                            goto next_arg;
                        } else {
                            print_usage();
                            return 1;
                        }
                    default:
                        print_usage();
                        return 1;
                }
            }
        } else {
            *directory = argv[i];
        }
        next_arg:;
    }
    
    return 0;
}

int main(int argc, char **argv)
{
    options_t opts;
    char *directory;
    count_t count = {0, 0};
    int is_last[1000] = {0};
    struct stat st;
    
    if (parse_args(argc, argv, &opts, &directory) != 0)
        return 1;
    
    if (stat(directory, &st) != 0) {
        my_write("tree: ");
        my_write(directory);
        my_write(": No such file or directory\n");
        return 1;
    }
    
    if (!S_ISDIR(st.st_mode)) {
        my_write("tree: ");
        my_write(directory);
        my_write(": Not a directory\n");
        return 1;
    }
    
    // Print root directory
    my_write(directory);
    my_write("\n");
    count.dirs++;
    
    print_tree(directory, &opts, 0, is_last, &count);
    
    // Print summary
    my_write("\n");
    // Simple number printing
    if (count.dirs > 0) {
        char num_str[20];
        my_itoa(count.dirs - 1, num_str); // Don't count root
        my_write(num_str);
        my_write(" director");
        if (count.dirs - 1 != 1)
            my_write("ies");
        else
            my_write("y");
    }
    
    if (!opts.dirs_only) {
        if (count.dirs > 0)
            my_write(", ");
        char num_str[20];
        my_itoa(count.files, num_str);
        my_write(num_str);
        my_write(" file");
        if (count.files != 1)
            my_write("s");
    }
    my_write("\n");
    
    return 0;
}
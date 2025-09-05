/*
** EPITECH PROJECT, 2025
** Tree
** File description:
** tree_display
*/

#include "tree.h"

void print_tree_recursive(char *path, options_t *opts, char *prefix, 
    int depth, counters_t *counters)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    struct stat file_stat;
    char *full_path = NULL;
    char *new_prefix = NULL;
    int is_last = 0;
    int count = 0;
    char **entries = NULL;
    int i = 0;
    int j = 0;

    if (opts->max_depth != -1 && depth >= opts->max_depth)
        return;
    dir = opendir(path);
    if (!dir) {
        write(STDERR_FILENO, "tree: cannot open directory ", 29);
        write(STDERR_FILENO, path, my_strlen(path));
        write(STDERR_FILENO, ": Permission denied\n", 20);
        return;
    }
    entries = malloc(1000 * sizeof(char *));
    if (!entries) {
        closedir(dir);
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (!opts->show_all && is_hidden(entry->d_name))
            continue;
        full_path = join_path(path, entry->d_name);
        if (!full_path)
            continue;
        if (stat(full_path, &file_stat) == 0) {
            if (opts->dirs_only && !S_ISDIR(file_stat.st_mode)) {
                free(full_path);
                continue;
            }
            entries[count] = my_strdup(entry->d_name);
            if (entries[count])
                count++;
        }
        free(full_path);
    }
    closedir(dir);
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (strcmp(entries[i], entries[j]) > 0) {
                char *temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
        }
    }
    for (i = 0; i < count; i++) {
        is_last = (i == count - 1);
        full_path = join_path(path, entries[i]);
        if (!full_path)
            continue;
        if (stat(full_path, &file_stat) == 0) {
            write(STDOUT_FILENO, prefix, my_strlen(prefix));
            if (is_last) {
                write(STDOUT_FILENO, "`-- ", 4);
            } else {
                write(STDOUT_FILENO, "|-- ", 4);
            }
            if (opts->show_full_path) {
                write(STDOUT_FILENO, full_path, my_strlen(full_path));
            } else {
                write(STDOUT_FILENO, entries[i], my_strlen(entries[i]));
            }
            write(STDOUT_FILENO, "\n", 1);
            if (S_ISDIR(file_stat.st_mode)) {
                counters->dirs++;
                new_prefix = malloc((my_strlen(prefix) + 5) * sizeof(char));
                if (new_prefix) {
                    my_strcpy(new_prefix, prefix);
                    if (is_last) {
                        new_prefix[my_strlen(prefix)] = ' ';
                        new_prefix[my_strlen(prefix) + 1] = ' ';
                        new_prefix[my_strlen(prefix) + 2] = ' ';
                        new_prefix[my_strlen(prefix) + 3] = ' ';
                        new_prefix[my_strlen(prefix) + 4] = '\0';
                    } else {
                        new_prefix[my_strlen(prefix)] = '|';
                        new_prefix[my_strlen(prefix) + 1] = ' ';
                        new_prefix[my_strlen(prefix) + 2] = ' ';
                        new_prefix[my_strlen(prefix) + 3] = ' ';
                        new_prefix[my_strlen(prefix) + 4] = '\0';
                    }
                    print_tree_recursive(full_path, opts, new_prefix, depth + 1, counters);
                    free(new_prefix);
                }
            } else {
                counters->files++;
            }
        }
        free(full_path);
        free(entries[i]);
    }
    free(entries);
}
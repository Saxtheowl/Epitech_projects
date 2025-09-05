/*
** EPITECH PROJECT, 2025
** Tree
** File description:
** tree
*/

#include "tree.h"

void print_tree(char *path, options_t *opts, counters_t *counters)
{
    struct stat path_stat;

    counters->dirs = 0;
    counters->files = 0;
    if (stat(path, &path_stat) != 0) {
        write(STDERR_FILENO, "tree: ", 6);
        write(STDERR_FILENO, path, my_strlen(path));
        write(STDERR_FILENO, ": No such file or directory\n", 28);
        return;
    }
    if (!S_ISDIR(path_stat.st_mode)) {
        write(STDERR_FILENO, "tree: ", 6);
        write(STDERR_FILENO, path, my_strlen(path));
        write(STDERR_FILENO, ": Not a directory\n", 18);
        return;
    }
    if (opts->show_full_path) {
        write(STDOUT_FILENO, path, my_strlen(path));
    } else {
        write(STDOUT_FILENO, path, my_strlen(path));
    }
    write(STDOUT_FILENO, "\n", 1);
    counters->dirs = 1;
    print_tree_recursive(path, opts, "", 0, counters);
    write(STDOUT_FILENO, "\n", 1);
    if (opts->dirs_only) {
        char dirs_str[32];
        int dirs_count = counters->dirs - 1;
        int len = 0;
        int temp = dirs_count;
        
        if (dirs_count == 0)
            len = 1;
        else {
            while (temp > 0) {
                temp /= 10;
                len++;
            }
        }
        temp = dirs_count;
        dirs_str[len] = '\0';
        if (dirs_count == 0)
            dirs_str[0] = '0';
        else {
            while (temp > 0) {
                dirs_str[--len] = (temp % 10) + '0';
                temp /= 10;
            }
        }
        write(STDOUT_FILENO, dirs_str, my_strlen(dirs_str));
        write(STDOUT_FILENO, " directories\n", 13);
    } else {
        char dirs_str[32];
        char files_str[32];
        int dirs_count = counters->dirs - 1;
        int files_count = counters->files;
        int len = 0;
        int temp = 0;
        
        temp = dirs_count;
        if (dirs_count == 0)
            len = 1;
        else {
            while (temp > 0) {
                temp /= 10;
                len++;
            }
        }
        temp = dirs_count;
        dirs_str[len] = '\0';
        if (dirs_count == 0)
            dirs_str[0] = '0';
        else {
            while (temp > 0) {
                dirs_str[--len] = (temp % 10) + '0';
                temp /= 10;
            }
        }
        temp = files_count;
        len = 0;
        if (files_count == 0)
            len = 1;
        else {
            while (temp > 0) {
                temp /= 10;
                len++;
            }
        }
        temp = files_count;
        files_str[len] = '\0';
        if (files_count == 0)
            files_str[0] = '0';
        else {
            while (temp > 0) {
                files_str[--len] = (temp % 10) + '0';
                temp /= 10;
            }
        }
        write(STDOUT_FILENO, dirs_str, my_strlen(dirs_str));
        write(STDOUT_FILENO, " directories, ", 14);
        write(STDOUT_FILENO, files_str, my_strlen(files_str));
        write(STDOUT_FILENO, " files\n", 7);
    }
}

int tree_main(int argc, char **argv)
{
    options_t opts;
    char *path = NULL;
    counters_t counters;

    if (parse_options(argc, argv, &opts, &path) != 0)
        return 1;
    print_tree(path, &opts, &counters);
    return 0;
}
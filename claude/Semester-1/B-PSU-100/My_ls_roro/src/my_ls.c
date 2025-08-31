/*
** EPITECH PROJECT, 2024
** My_ls
** File description:
** Core my_ls functionality
*/

#include "../include/my_ls.h"

static int is_directory(char *path)
{
    struct stat st;

    if (stat(path, &st) == -1)
        return 0;
    return S_ISDIR(st.st_mode);
}

static int print_single_file(char *path, options_t *opts)
{
    struct stat st;
    file_info_t file;

    if (stat(path, &st) == -1) {
        perror(path);
        return -1;
    }
    file.name = path;
    file.full_path = path;
    file.stat_info = st;
    file.next = NULL;
    if (opts->l_flag)
        print_long_format(&file, opts);
    else {
        my_putstr(path);
        my_putchar('\n');
    }
    return 0;
}

static int handle_multiple_paths(char **files, int count, options_t *opts)
{
    int i = 0;
    int dirs = 0;
    int error = 0;

    while (i < count) {
        if (is_directory(files[i]))
            dirs++;
        i++;
    }
    i = 0;
    while (i < count) {
        if (!is_directory(files[i]) || opts->d_flag) {
            if (print_single_file(files[i], opts) == -1)
                error = 1;
        }
        i++;
    }
    i = 0;
    while (i < count) {
        if (is_directory(files[i]) && !opts->d_flag) {
            if ((count > 1 && dirs > 0) || (count > 1)) {
                my_putstr(files[i]);
                my_putstr(":\n");
            }
            if (list_directory(files[i], opts) == -1)
                error = 1;
            if (i < count - 1 && is_directory(files[i + 1]) && !opts->d_flag)
                my_putchar('\n');
        }
        i++;
    }
    return error ? -1 : 0;
}

int my_ls(options_t *opts, char **files, int file_count)
{
    if (file_count == 0)
        return list_directory(".", opts);
    if (file_count == 1) {
        if (!is_directory(files[0]) || opts->d_flag)
            return print_single_file(files[0], opts);
        return list_directory(files[0], opts);
    }
    return handle_multiple_paths(files, file_count, opts);
}
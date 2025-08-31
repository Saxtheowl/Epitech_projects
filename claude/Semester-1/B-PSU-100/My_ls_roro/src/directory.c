/*
** EPITECH PROJECT, 2024
** My_ls
** File description:
** Directory listing functionality
*/

#include "../include/my_ls.h"

static char *create_full_path(char *dir, char *name)
{
    int dir_len = my_strlen(dir);
    int name_len = my_strlen(name);
    char *path = malloc(dir_len + name_len + 2);

    if (!path)
        return NULL;
    my_strcpy(path, dir);
    if (dir[dir_len - 1] != '/')
        my_strcat(path, "/");
    my_strcat(path, name);
    return path;
}

static file_info_t *create_file_info(char *dir, char *name)
{
    file_info_t *file = malloc(sizeof(file_info_t));
    char *full_path;

    if (!file)
        return NULL;
    file->name = my_strdup(name);
    if (!file->name) {
        free(file);
        return NULL;
    }
    full_path = create_full_path(dir, name);
    if (!full_path) {
        free(file->name);
        free(file);
        return NULL;
    }
    file->full_path = full_path;
    if (lstat(full_path, &file->stat_info) == -1) {
        free(file->name);
        free(file->full_path);
        free(file);
        return NULL;
    }
    file->next = NULL;
    return file;
}

file_info_t *get_file_list(char *path, options_t *opts)
{
    DIR *dir = opendir(path);
    struct dirent *entry;
    file_info_t *head = NULL;
    file_info_t *current = NULL;
    file_info_t *new_file;

    if (!dir) {
        perror(path);
        return NULL;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (!opts->a_flag && entry->d_name[0] == '.')
            continue;
        new_file = create_file_info(path, entry->d_name);
        if (new_file) {
            if (!head)
                head = new_file;
            else
                current->next = new_file;
            current = new_file;
        }
    }
    closedir(dir);
    return head;
}

int list_directory(char *path, options_t *opts)
{
    file_info_t *files = get_file_list(path, opts);
    file_info_t *current;

    if (!files)
        return -1;
    sort_files(&files, opts);
    print_files(files, opts, path);
    if (opts->R_flag) {
        current = files;
        while (current) {
            if (S_ISDIR(current->stat_info.st_mode) &&
                my_strcmp(current->name, ".") != 0 &&
                my_strcmp(current->name, "..") != 0) {
                my_putchar('\n');
                my_putstr(current->full_path);
                my_putstr(":\n");
                list_directory(current->full_path, opts);
            }
            current = current->next;
        }
    }
    free_file_list(files);
    return 0;
}
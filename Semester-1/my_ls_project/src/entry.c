/*
** EPITECH PROJECT, 2025
** MY_LS
** File description:
** Epitech-style source file for my_ls project
*/
#include "my_ls.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

static int should_skip(const char *name, options_t *opts)
{
    if (opts->a_opt)
        return 0;
    return name[0] == '.';
}

static int fill_link(entry_t *e)
{
    if (!S_ISLNK(e->st.st_mode))
        return 0;
    e->is_link = 1;
    e->link_len = readlink(e->path, e->link_target, sizeof(e->link_target) - 1);
    if (e->link_len >= 0)
        e->link_target[e->link_len] = '\0';
    else
        e->link_len = 0;
    return 0;
}

int read_entries(const char *path, options_t *opts, entry_t **out, size_t *n)
{
    DIR *dir;
    struct dirent *de;
    size_t cap = 16;
    size_t i = 0;
    entry_t *arr;
    char full[PATH_MAX];
    size_t path_len = my_strlen(path);

    dir = opendir(path);
    if (!dir)
        return -1;
    arr = (entry_t *)malloc(sizeof(entry_t) * cap);
    if (!arr) {
        closedir(dir);
        return -1;
    }
    while ((de = readdir(dir)) != NULL) {
        if (should_skip(de->d_name, opts))
            continue;
        if (i == cap) {
            cap *= 2;
            entry_t *narr = (entry_t *)realloc(arr, sizeof(entry_t) * cap);
            if (!narr) {
                free(arr);
                closedir(dir);
                return -1;
            }
            arr = narr;
        }
        arr[i].name = my_strdup(de->d_name);
        if (!arr[i].name) {
            closedir(dir);
            free(arr);
            return -1;
        }
        if (path_len + 1 + my_strlen(de->d_name) + 1 >= sizeof(full)) {
            closedir(dir);
            free(arr[i].name);
            free(arr);
            return -1;
        }
        for (size_t k = 0; k < path_len; k++)
            full[k] = path[k];
        if (path_len > 0 && path[path_len - 1] != '/') {
            full[path_len] = '/';
            full[path_len + 1] = '\0';
        } else {
            full[path_len] = '\0';
        }
        size_t off = my_strlen(full);
        for (size_t k = 0; de->d_name[k] != '\0'; k++)
            full[off + k] = de->d_name[k];
        full[off + my_strlen(de->d_name)] = '\0';
        arr[i].path = my_strdup(full);
        if (!arr[i].path) {
            closedir(dir);
            free(arr[i].name);
            free(arr);
            return -1;
        }
        if (lstat(arr[i].path, &arr[i].st) < 0) {
            closedir(dir);
            free(arr[i].name);
            free(arr[i].path);
            free(arr);
            return -1;
        }
        arr[i].is_link = 0;
        arr[i].link_len = 0;
        arr[i].link_target[0] = '\0';
        fill_link(&arr[i]);
        i++;
    }
    closedir(dir);
    *out = arr;
    *n = i;
    return 0;
}

void free_entries(entry_t *arr, size_t n)
{
    size_t i = 0;

    while (i < n) {
        free(arr[i].name);
        free(arr[i].path);
        i++;
    }
    free(arr);
}

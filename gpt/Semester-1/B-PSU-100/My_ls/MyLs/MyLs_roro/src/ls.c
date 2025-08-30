/*
** EPITECH PROJECT, 2025
** MyLs_roro
** File description:
** List logic
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "my_ls.h"

void sort_entries(entry_t *arr, int n, const flags_t *f);
void print_long(const entry_t *e);

static entry_t *append_entry(entry_t *arr, int *n, const char *dir,
    const char *name)
{
    entry_t *tmp;
    char *path;

    tmp = realloc(arr, (size_t)(*n + 1) * sizeof(entry_t));
    if (!tmp)
        return NULL;
    arr = tmp;
    arr[*n].name = strdup(name);
    if (!arr[*n].name)
        return NULL;
    if (dir) {
        size_t dl = strlen(dir);
        size_t nl = strlen(name);
        path = malloc(dl + 1 + nl + 1);
        if (!path)
            return NULL;
        memcpy(path, dir, dl);
        path[dl] = '/';
        memcpy(path + dl + 1, name, nl + 1);
    } else {
        path = strdup(name);
        if (!path)
            return NULL;
    }
    arr[*n].path = path;
    if (lstat(path, &arr[*n].st) == -1) {
        arr[*n].st.st_mtime = 0;
    }
    *n += 1;
    return arr;
}

static int list_dir(const char *path, const flags_t *f)
{
    DIR *d;
    struct dirent *de;
    entry_t *arr;
    int n;
    int i;

    d = opendir(path);
    if (!d)
        return -1;
    arr = NULL;
    n = 0;
    while ((de = readdir(d)) != NULL) {
        if (!f->a && de->d_name[0] == '.')
            continue;
        arr = append_entry(arr, &n, path, de->d_name);
        if (!arr) { closedir(d); return -1; }
    }
    closedir(d);
    sort_entries(arr, n, f);
    for (i = 0; i < n; ++i) {
        if (f->l)
            print_long(&arr[i]);
        else
            printf("%s\n", arr[i].name);
    }
    if (f->R) {
        for (i = 0; i < n; ++i) {
            if (S_ISDIR(arr[i].st.st_mode) &&
                strcmp(arr[i].name, ".") != 0 &&
                strcmp(arr[i].name, "..") != 0) {
                printf("\n%s:\n", arr[i].path);
                my_ls_path(arr[i].path, f, 0);
            }
        }
    }
    free_entries(arr, n);
    return 0;
}

int my_ls_path(const char *path, const flags_t *f, int print_head)
{
    entry_t *arr;
    int n;

    if (print_head)
        printf("%s:\n", path);
    if (f->d) {
        arr = NULL;
        n = 0;
        arr = append_entry(arr, &n, NULL, path);
        if (!arr)
            return -1;
        if (f->l)
            print_long(&arr[0]);
        else
            printf("%s\n", arr[0].name);
        free_entries(arr, n);
        return 0;
    }
    return list_dir(path, f);
}

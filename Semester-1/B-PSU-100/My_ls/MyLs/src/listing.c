/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Handle CLI paths (files and directories) and printing headers.
*/
#include "my_ls.h"
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct path_item_s {
    char *arg;
    struct stat st;
    int kind; /* 0 error, 1 file, 2 dir */
    int errnum;
} path_item_t;

static int classify(const char *p, path_item_t *it)
{
    it->arg = my_strdup(p);
    if (lstat(p, &it->st) == -1) {
        it->kind = 0;
        it->errnum = errno;
        return -1;
    }
    if (S_ISDIR(it->st.st_mode) && !S_ISLNK(it->st.st_mode))
        it->kind = 2;
    else
        it->kind = 1;
    return 0;
}

static void free_items(path_item_t *arr, size_t n)
{
    for (size_t i = 0; i < n; ++i) free(arr[i].arg);
}

int list_paths(int ac, char **av, int first_path, const options_t *opts)
{
    if (first_path >= ac) {
        return list_directory(".", opts, false) == 0 ? 0 : -1;
    }

    size_t n = (size_t)(ac - first_path);
    path_item_t *items = (path_item_t *)xmalloc(sizeof(path_item_t) * n);
    size_t i;
    int had_error = 0;
    for (i = 0; i < n; ++i) {
        if (classify(av[first_path + (int)i], &items[i]) == -1) {
            my_perror_path("my_ls", av[first_path + (int)i], items[i].errnum);
            had_error = 1;
        }
    }

    /* First print non-directory arguments */
    int printed_any = 0;
    for (i = 0; i < n; ++i) {
        if (items[i].kind == 1) {
            /* List as a single item */
            options_t tmp = *opts;
            tmp.opt_d = true;
            if (list_directory(items[i].arg, &tmp, false) != 0)
                had_error = 1;
            printed_any = 1;
        }
    }
    /* Then directories */
    for (i = 0; i < n; ++i) {
        if (items[i].kind == 2) {
            if (printed_any || n > 1) {
                my_putstr_fd(1, items[i].arg);
                my_putstr_fd(1, ":
");
            }
            if (list_directory(items[i].arg, opts, false) != 0)
                had_error = 1;
            if (i + 1 < n) my_putstr_fd(1, "\n");
            printed_any = 1;
        }
    }

    free_items(items, n);
    free(items);
    return had_error ? -1 : 0;
}

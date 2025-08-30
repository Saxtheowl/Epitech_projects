/*
** EPITECH PROJECT, 2025
** MyLs_roro
** File description:
** Sorting helpers
*/

#include <stdlib.h>
#include <string.h>
#include "my_ls.h"

static int cmp_name(const void *a, const void *b)
{
    const entry_t *ea = a;
    const entry_t *eb = b;

    return strcmp(ea->name, eb->name);
}

static int cmp_mtime(const void *a, const void *b)
{
    const entry_t *ea = a;
    const entry_t *eb = b;

    if (ea->st.st_mtime == eb->st.st_mtime)
        return strcmp(ea->name, eb->name);
    return (ea->st.st_mtime < eb->st.st_mtime) ? 1 : -1;
}

void sort_entries(entry_t *arr, int n, const flags_t *f)
{
    if (f->t)
        qsort(arr, (size_t)n, sizeof(entry_t), cmp_mtime);
    else
        qsort(arr, (size_t)n, sizeof(entry_t), cmp_name);
    if (f->r) {
        int i;
        for (i = 0; i < n / 2; ++i) {
            entry_t tmp = arr[i];
            arr[i] = arr[n - 1 - i];
            arr[n - 1 - i] = tmp;
        }
    }
}

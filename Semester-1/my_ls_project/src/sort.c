/*
** EPITECH PROJECT, 2025
** MY_LS
** File description:
** Epitech-style source file for my_ls project
*/
#include "my_ls.h"
#include <stdlib.h>

static int cmp_name(entry_t *a, entry_t *b)
{
    return my_strcmp(a->name, b->name);
}

static int cmp_mtime(entry_t *a, entry_t *b)
{
    if (a->st.st_mtime == b->st.st_mtime)
        return cmp_name(a, b);
    return (a->st.st_mtime > b->st.st_mtime) ? -1 : 1;
}

static void merge(entry_t *arr, entry_t *tmp, size_t l, size_t m, size_t r,
    int (*cmp)(entry_t*, entry_t*))
{
    size_t i = l;
    size_t j = m;
    size_t k = l;

    while (i < m && j < r) {
        if (cmp(&arr[i], &arr[j]) <= 0)
            tmp[k++] = arr[i++];
        else
            tmp[k++] = arr[j++];
    }
    while (i < m)
        tmp[k++] = arr[i++];
    while (j < r)
        tmp[k++] = arr[j++];
    for (i = l; i < r; i++)
        arr[i] = tmp[i];
}

static void mergesort(entry_t *arr, entry_t *tmp, size_t l, size_t r,
    int (*cmp)(entry_t*, entry_t*))
{
    size_t m;

    if (r - l <= 1)
        return;
    m = l + (r - l) / 2;
    mergesort(arr, tmp, l, m, cmp);
    mergesort(arr, tmp, m, r, cmp);
    merge(arr, tmp, l, m, r, cmp);
}

void sort_entries(entry_t *arr, size_t n, int t_opt, int r_opt)
{
    entry_t *tmp;
    size_t i = 0;
    size_t j;

    if (n < 2)
        return;
    tmp = (entry_t *)malloc(sizeof(entry_t) * n);
    if (!tmp)
        return;
    mergesort(arr, tmp, 0, n, t_opt ? cmp_mtime : cmp_name);
    free(tmp);
    if (r_opt) {
        while (i < n / 2) {
            j = n - 1 - i;
            entry_t t = arr[i];

            arr[i] = arr[j];
            arr[j] = t;
            i++;
        }
    }
}

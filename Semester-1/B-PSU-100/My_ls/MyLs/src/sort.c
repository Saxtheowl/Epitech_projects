/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Simple stable-ish merge sort for entries.
*/
#include "my_ls.h"
#include <stdlib.h>

static int cmp_name(const entry_t *a, const entry_t *b)
{
    return my_strcmp(a->name, b->name);
}

static long long get_mtime_ns(const entry_t *e)
{
#if defined(__APPLE__) || defined(__MACH__)
    return (long long)e->st.st_mtimespec.tv_sec * 1000000000LL
         + (long long)e->st.st_mtimespec.tv_nsec;
#else
    return (long long)e->st.st_mtim.tv_sec * 1000000000LL
         + (long long)e->st.st_mtim.tv_nsec;
#endif
}

static int cmp_time_then_name(const entry_t *a, const entry_t *b)
{
    long long ta = get_mtime_ns(a);
    long long tb = get_mtime_ns(b);
    if (ta == tb) return cmp_name(a, b);
    return (ta > tb) ? -1 : 1; /* newer first */
}

static void merge(entry_t *arr, entry_t *tmp, size_t l, size_t m, size_t r, int (*cmp)(const entry_t*, const entry_t*))
{
    size_t i = l, j = m, k = l;
    while (i < m && j < r) {
        if (cmp(&arr[i], &arr[j]) <= 0) tmp[k++] = arr[i++];
        else tmp[k++] = arr[j++];
    }
    while (i < m) tmp[k++] = arr[i++];
    while (j < r) tmp[k++] = arr[j++];
    for (size_t x = l; x < r; ++x) arr[x] = tmp[x];
}

static void mergesort(entry_t *arr, entry_t *tmp, size_t l, size_t r, int (*cmp)(const entry_t*, const entry_t*))
{
    if (r - l <= 1) return;
    size_t m = l + (r - l) / 2;
    mergesort(arr, tmp, l, m, cmp);
    mergesort(arr, tmp, m, r, cmp);
    merge(arr, tmp, l, m, r, cmp);
}

void sort_entries(entry_t *arr, size_t n, bool by_time, bool reverse)
{
    if (!arr || n <= 1) return;
    entry_t *tmp = (entry_t *)xmalloc(sizeof(entry_t) * n);
    int (*cmp)(const entry_t*, const entry_t*) = by_time ? cmp_time_then_name : cmp_name;
    mergesort(arr, tmp, 0, n, cmp);
    free(tmp);
    if (reverse) {
        for (size_t i = 0; i < n / 2; ++i) {
            entry_t t = arr[i];
            arr[i] = arr[n - 1 - i];
            arr[n - 1 - i] = t;
        }
    }
}

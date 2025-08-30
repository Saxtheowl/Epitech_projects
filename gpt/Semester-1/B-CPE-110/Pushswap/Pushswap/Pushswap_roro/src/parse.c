/*
** EPITECH PROJECT, 2025
** Pushswap_roro
** File description:
** Parse arguments and compress values
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pushswap.h"

static int add_num(vec_t *v, const char *s)
{
    char *end;
    long val;

    if (*s == '\0')
        return -1;
    val = strtol(s, &end, 10);
    if (end == s || *end != '\0')
        return -1;
    if (val < -2147483648L || val > 2147483647L)
        return -1;
    return vec_push(v, (int)val);
}

static int split_and_add(vec_t *v, const char *s)
{
    const char *p = s;
    while (*p) {
        while (*p == ' ' || *p == '\t')
            ++p;
        if (*p == '\0')
            break;
        {
            const char *q = p;
            char tmp[64];
            int i = 0;
            while (*q && *q != ' ' && *q != '\t' && i < 63) {
                tmp[i++] = *q++;
            }
            tmp[i] = '\0';
            if (add_num(v, tmp) != 0)
                return -1;
            p = q;
        }
    }
    return 0;
}

int parse_args(int ac, char **av, vec_t *out)
{
    int i;

    vec_init(out);
    for (i = 1; i < ac; ++i) {
        if (strchr(av[i], ' ') || strchr(av[i], '\t')) {
            if (split_and_add(out, av[i]) != 0)
                return -1;
        } else {
            if (add_num(out, av[i]) != 0)
                return -1;
        }
    }
    return 0;
}

static int cmp_int(const void *a, const void *b)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;

    return (ia > ib) - (ia < ib);
}

int compress_values(vec_t *v)
{
    int *tmp;
    int i;

    if (v->size <= 0)
        return 0;
    tmp = malloc((size_t)v->size * sizeof(int));
    if (!tmp)
        return -1;
    for (i = 0; i < v->size; ++i)
        tmp[i] = v->data[i];
    qsort(tmp, (size_t)v->size, sizeof(int), cmp_int);
    for (i = 1; i < v->size; ++i) {
        if (tmp[i] == tmp[i - 1]) {
            free(tmp);
            return -1;
        }
    }
    for (i = 0; i < v->size; ++i) {
        int lo = 0, hi = v->size - 1, mid, idx = -1;
        while (lo <= hi) {
            mid = (lo + hi) / 2;
            if (tmp[mid] == v->data[i]) { idx = mid; break; }
            if (tmp[mid] < v->data[i]) lo = mid + 1; else hi = mid - 1;
        }
        v->data[i] = idx;
    }
    free(tmp);
    return 0;
}

int is_sorted(const vec_t *v)
{
    int i;

    for (i = 1; i < v->size; ++i) {
        if (v->data[i - 1] > v->data[i])
            return 0;
    }
    return 1;
}

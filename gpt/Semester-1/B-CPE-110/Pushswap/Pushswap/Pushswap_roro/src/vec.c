/*
** EPITECH PROJECT, 2025
** Pushswap_roro
** File description:
** Simple vector and ops buffer
*/

#include <stdlib.h>
#include <string.h>
#include "pushswap.h"

int vec_init(vec_t *v)
{
    v->data = NULL;
    v->size = 0;
    v->cap = 0;
    return 0;
}

void vec_free(vec_t *v)
{
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->cap = 0;
}

static int vec_grow(vec_t *v, int need)
{
    int nc;
    int *nd;

    if (v->size + need <= v->cap)
        return 0;
    nc = v->cap ? v->cap * 2 : 8;
    while (nc < v->size + need)
        nc *= 2;
    nd = realloc(v->data, (size_t)nc * sizeof(int));
    if (!nd)
        return -1;
    v->data = nd;
    v->cap = nc;
    return 0;
}

int vec_push(vec_t *v, int x)
{
    if (vec_grow(v, 1) != 0)
        return -1;
    v->data[v->size++] = x;
    return 0;
}

int vec_push_front(vec_t *v, int x)
{
    if (vec_grow(v, 1) != 0)
        return -1;
    memmove(&v->data[1], &v->data[0], (size_t)v->size * sizeof(int));
    v->data[0] = x;
    v->size += 1;
    return 0;
}

int vec_pop_front(vec_t *v, int *out)
{
    if (v->size <= 0)
        return -1;
    if (out)
        *out = v->data[0];
    memmove(&v->data[0], &v->data[1], (size_t)(v->size - 1) * sizeof(int));
    v->size -= 1;
    return 0;
}

int vec_rotate(vec_t *v)
{
    int x;

    if (v->size <= 1)
        return 0;
    x = v->data[0];
    memmove(&v->data[0], &v->data[1], (size_t)(v->size - 1) * sizeof(int));
    v->data[v->size - 1] = x;
    return 0;
}

int vec_rrotate(vec_t *v)
{
    int x;

    if (v->size <= 1)
        return 0;
    x = v->data[v->size - 1];
    memmove(&v->data[1], &v->data[0], (size_t)(v->size - 1) * sizeof(int));
    v->data[0] = x;
    return 0;
}

int ops_init(ops_t *o)
{
    o->buf = NULL;
    o->len = 0;
    o->cap = 0;
    return 0;
}

void ops_free(ops_t *o)
{
    free(o->buf);
    o->buf = NULL;
    o->len = 0;
    o->cap = 0;
}

static int ops_grow(ops_t *o, int need)
{
    int nc;
    char *nb;

    if (o->len + need <= o->cap)
        return 0;
    nc = o->cap ? o->cap * 2 : 64;
    while (nc < o->len + need)
        nc *= 2;
    nb = realloc(o->buf, (size_t)nc);
    if (!nb)
        return -1;
    o->buf = nb;
    o->cap = nc;
    return 0;
}

int ops_add(ops_t *o, const char *op)
{
    int n = 0;

    while (op[n])
        n += 1;
    if (o->len > 0) {
        if (ops_grow(o, n + 1) != 0)
            return -1;
        o->buf[o->len++] = ' ';
    } else {
        if (ops_grow(o, n) != 0)
            return -1;
    }

    memcpy(o->buf + o->len, op, (size_t)n);
    o->len += n;
    return 0;
}

/*
** EPITECH PROJECT, 2025
** Wolfram_roro
** File description:
** sim.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "wolfram.h"

static int cmp_int(const void *a, const void *b)
{
    int ia;
    int ib;

    ia = *(const int *)a;
    ib = *(const int *)b;
    if (ia < ib)
        return -1;
    if (ia > ib)
        return 1;
    return 0;
}

void cells_init_single(Cells *c)
{
    c->len = 1;
    c->cap = 4;
    c->pos = malloc((size_t)c->cap * sizeof(int));
    if (c->pos)
        c->pos[0] = 0;
}

void cells_free(Cells *c)
{
    free(c->pos);
    c->pos = NULL;
    c->len = 0;
    c->cap = 0;
}

static bool has_cell(const Cells *c, int x)
{
    return bsearch(&x, c->pos, (size_t)c->len, sizeof(int), cmp_int) != NULL;
}

static int rule_bit(int rule, bool a, bool b, bool d)
{
    int idx;

    idx = (a ? 4 : 0) + (b ? 2 : 0) + (d ? 1 : 0);
    return (rule >> idx) & 1;
}

void cells_step(const Cells *cur, Cells *next, int rule)
{
    int mn;
    int mx;
    int i;

    if (cur->len == 0) {
        next->len = 0;
        return;
    }
    mn = cur->pos[0];
    mx = cur->pos[cur->len - 1];
    if (next->cap < (mx - mn + 3)) {
        next->cap = (mx - mn + 3) * 2;
        next->pos = realloc(next->pos, (size_t)next->cap * sizeof(int));
    }
    next->len = 0;
    for (i = mn - 1; i <= mx + 1; ++i) {
        bool a;
        bool b;
        bool d;
        int alive;

        a = has_cell(cur, i - 1);
        b = has_cell(cur, i);
        d = has_cell(cur, i + 1);
        alive = rule_bit(rule, a, b, d);
        if (alive) {
            next->pos[next->len++] = i;
        }
    }
}

void print_window(const Cells *c, int window, int move)
{
    int left;
    int i;

    left = move - (window / 2);
    for (i = 0; i < window; ++i) {
        int x;
        char ch;
        x = left + i;
        ch = has_cell(c, x) ? '*' : ' ';
        putchar(ch);
    }
    putchar('\n');
}


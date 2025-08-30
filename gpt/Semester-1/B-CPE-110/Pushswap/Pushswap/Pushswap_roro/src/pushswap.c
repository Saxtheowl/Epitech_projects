/*
** EPITECH PROJECT, 2025
** Pushswap_roro
** File description:
** Core algorithm (LSD radix on compressed indices)
*/

#include <stdio.h>
#include <stdlib.h>
#include "pushswap.h"

/* keep for potential small-sorts; unused in radix path */
__attribute__((unused)) static void op_sa(vec_t *a, ops_t *o)
{
    int t;

    if (a->size >= 2) {
        t = a->data[0];
        a->data[0] = a->data[1];
        a->data[1] = t;
        ops_add(o, "sa");
    }
}

static void op_pa(vec_t *a, vec_t *b, ops_t *o)
{
    int x;

    if (b->size <= 0)
        return;
    vec_pop_front(b, &x);
    vec_push_front(a, x);
    ops_add(o, "pa");
}

static void op_pb(vec_t *a, vec_t *b, ops_t *o)
{
    int x;

    if (a->size <= 0)
        return;
    vec_pop_front(a, &x);
    vec_push_front(b, x);
    ops_add(o, "pb");
}

static void op_ra(vec_t *a, ops_t *o)
{
    vec_rotate(a);
    ops_add(o, "ra");
}

/* keep for potential optimizations; unused in radix path */
__attribute__((unused)) static void op_rra(vec_t *a, ops_t *o)
{
    vec_rrotate(a);
    ops_add(o, "rra");
}

int run_pushswap(int ac, char **av)
{
    vec_t a;
    vec_t b;
    ops_t ops;
    int i;
    int maxv;
    int bits;

    if (ac <= 1)
        return 0;
    if (parse_args(ac, av, &a) != 0)
        return ERR_CODE;
    if (compress_values(&a) != 0) {
        vec_free(&a);
        return ERR_CODE;
    }
    if (is_sorted(&a)) {
        vec_free(&a);
        return 0;
    }
    vec_init(&b);
    ops_init(&ops);
    maxv = 0;
    for (i = 0; i < a.size; ++i)
        if (a.data[i] > maxv) maxv = a.data[i];
    bits = 0;
    while ((maxv >> bits) != 0)
        bits += 1;
    for (i = 0; i < bits; ++i) {
        int j;
        int n = a.size;
        for (j = 0; j < n; ++j) {
            int v = a.data[0];
            if (((v >> i) & 1) == 0)
                op_pb(&a, &b, &ops);
            else
                op_ra(&a, &ops);
        }
        while (b.size > 0)
            op_pa(&a, &b, &ops);
    }
    if (ops.len > 0)
        fwrite(ops.buf, 1, (size_t)ops.len, stdout);
    putchar('\n');
    ops_free(&ops);
    vec_free(&a);
    vec_free(&b);
    return 0;
}

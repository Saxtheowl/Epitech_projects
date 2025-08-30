/*
** EPITECH PROJECT, 2025
** Bistro_matic_roro
** File description:
** Base and ops helpers
*/

#include <stdlib.h>
#include <string.h>
#include "bistro.h"

static void map_clear(int *m)
{
    int i;

    for (i = 0; i < 256; ++i)
        m[i] = -1;
}

int base_init(base_t *bs, const char *digits, const char *ops)
{
    int i;
    int j;

    bs->digits = digits;
    bs->b = (int)strlen(digits);
    if (bs->b < 2)
        return -1;
    map_clear(bs->map);
    for (i = 0; i < bs->b; ++i) {
        unsigned char ch = (unsigned char)digits[i];
        if (bs->map[ch] != -1)
            return -1;
        bs->map[ch] = i;
    }
    for (i = 0; ops[i]; ++i) {
        for (j = i + 1; ops[j]; ++j)
            if (ops[i] == ops[j])
                return -1;
    }
    bs->op_lpar = ops[0];
    bs->op_rpar = ops[1];
    bs->op_add = ops[2];
    bs->op_sub = ops[3];
    bs->op_neg = ops[3];
    bs->op_mul = ops[4];
    bs->op_div = ops[5];
    bs->op_mod = ops[6];
    return 0;
}

long skip_ws(ctx_t *c)
{
    long n;

    n = 0;
    while (c->p < c->end && (*c->p == ' ' || *c->p == '\t' || *c->p == '\n')) {
        c->p += 1;
        n += 1;
    }
    return n;
}

int is_op(ctx_t *c, char ch, char *which)
{
    (void)c;
    *which = 0;
    if (ch == 0)
        return 0;
    *which = ch;
    return 1;
}

/*
** EPITECH PROJECT, 2025
** Bistro_matic_roro
** File description:
** eval_expr entry point
*/

#include <stdlib.h>
#include <string.h>
#include "bistro.h"

char *eval_expr(const char *base, const char *ops,
    const char *expr, unsigned int size)
{
    ctx_t c;
    bigint_t v;
    char *out;

    c.p = expr;
    c.end = expr + size;
    if (base_init(&c.bs, base, ops) != 0)
        return NULL;
    if (parse_expr(&c, &v) != 0)
        return NULL;
    /* ensure full consumption (ignoring trailing whitespace) */
    while (c.p < c.end && (*c.p == ' ' || *c.p == '\t' || *c.p == '\n'))
        c.p += 1;
    if (c.p != c.end) {
        bi_free(&v);
        return NULL;
    }
    out = bi_to_str(&v, &c.bs);
    bi_free(&v);
    return out;
}

/*
** EPITECH PROJECT, 2025
** Bistro_matic_roro
** File description:
** Parser and evaluator
*/

#include <stdlib.h>
#include <string.h>
#include "bistro.h"

static int read_number(ctx_t *c, bigint_t *out)
{
    const char *start;
    const char *p;

    start = c->p;
    p = c->p;
    while (p < c->end && c->bs.map[(unsigned char)*p] >= 0)
        p += 1;
    if (p == start)
        return -1;
    {
        char *tmp = malloc((size_t)(p - start + 1));
        int i;
        for (i = 0; start + i < p; ++i)
            tmp[i] = start[i];
        tmp[i] = '\0';
        bi_from_str(out, tmp, &c->bs);
        free(tmp);
    }
    c->p = p;
    return 0;
}

int parse_number(ctx_t *c, bigint_t *out)
{
    skip_ws(c);
    if (read_number(c, out) != 0)
        return -1;
    return 0;
}

int parse_factor(ctx_t *c, bigint_t *out)
{
    skip_ws(c);
    if (c->p < c->end && *c->p == c->bs.op_lpar) {
        bigint_t val;
        int st;
        c->p += 1;
        st = parse_expr(c, &val);
        if (st != 0)
            return -1;
        skip_ws(c);
        if (!(c->p < c->end && *c->p == c->bs.op_rpar)) {
            bi_free(&val);
            return -1;
        }
        c->p += 1;
        *out = val;
        return 0;
    }
    if (c->p < c->end && *c->p == c->bs.op_neg) {
        bigint_t val;
        int st2;
        c->p += 1;
        st2 = parse_factor(c, &val);
        if (st2 != 0)
            return -1;
        val.sign *= -1;
        *out = val;
        return 0;
    }
    return parse_number(c, out);
}


int parse_term(ctx_t *c, bigint_t *out)
{
    bigint_t lhs;
    int st;

    st = parse_factor(c, &lhs);
    if (st != 0)
        return -1;
    while (1) {
        skip_ws(c);
        if (c->p >= c->end)
            break;
        if (*c->p == c->bs.op_mul || *c->p == c->bs.op_div || *c->p == c->bs.op_mod) {
            char op = *c->p;
            bigint_t rhs;
            bigint_t res;
            bigint_t q;
            bigint_t m;
            c->p += 1;
            if (parse_factor(c, &rhs) != 0) { bi_free(&lhs); return -1; }
            if (op == c->bs.op_mul) {
                bi_init(&res);
                bi_mul(&res, &lhs, &rhs, &c->bs);
                bi_free(&lhs); bi_free(&rhs);
                lhs = res;
            } else {
                bi_init(&q); bi_init(&m);
                if (bi_divmod(&q, &m, &lhs, &rhs, &c->bs) != 0) { bi_free(&lhs); bi_free(&rhs); return -1; }
                bi_free(&lhs); bi_free(&rhs);
                if (op == c->bs.op_div) { lhs = q; bi_free(&m); }
                else { lhs = m; bi_free(&q); }
            }
        } else {
            break;
        }
    }
    *out = lhs;
    return 0;
}

int parse_expr(ctx_t *c, bigint_t *out)
{
    bigint_t lhs;
    int st;

    st = parse_term(c, &lhs);
    if (st != 0)
        return -1;
    while (1) {
        bigint_t rhs;
        bigint_t res;

        bi_init(&rhs); bi_init(&res);
        skip_ws(c);
        if (c->p >= c->end)
            break;
        if (*c->p == c->bs.op_add || *c->p == c->bs.op_sub) {
            char op = *c->p;
            c->p += 1;
            if (parse_term(c, &rhs) != 0) { bi_free(&lhs); return -1; }
            if (op == c->bs.op_add)
                bi_add(&res, &lhs, &rhs, &c->bs);
            else
                bi_sub(&res, &lhs, &rhs, &c->bs);
            bi_free(&lhs); bi_free(&rhs);
            lhs = res;
        } else {
            break;
        }
    }
    *out = lhs;
    return 0;
}

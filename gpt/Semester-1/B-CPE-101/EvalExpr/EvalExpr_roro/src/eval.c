/*
** EPITECH PROJECT, 2025
** EvalExpr_roro
** File description:
** Recursive descent expression evaluator
*/

#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include "eval.h"

typedef struct ctx_s {
    const char *p;
} ctx_t;

static void skip_ws(ctx_t *c)
{
    while (*c->p == ' ' || *c->p == '\t')
        c->p += 1;
}

static long parse_number(ctx_t *c, int *ok)
{
    long v;
    int sign;

    skip_ws(c);
    v = 0;
    sign = 1;
    if (*c->p == '+') {
        c->p += 1;
    } else if (*c->p == '-') {
        sign = -1;
        c->p += 1;
    }
    if (!isdigit((unsigned char)*c->p)) {
        *ok = 0;
        return 0;
    }
    while (isdigit((unsigned char)*c->p)) {
        int d = *c->p - '0';
        if (v > (LONG_MAX - d) / 10) {
            *ok = 0;
            return 0;
        }
        v = v * 10 + d;
        c->p += 1;
    }
    return sign * v;
}

static long parse_factor(ctx_t *c, int *ok);

static long parse_paren_or_num(ctx_t *c, int *ok)
{
    long v;

    skip_ws(c);
    if (*c->p == '(') {
        c->p += 1;
        v = parse_factor(c, ok);
        if (!*ok)
            return 0;
        skip_ws(c);
        if (*c->p != ')') {
            *ok = 0;
            return 0;
        }
        c->p += 1;
        return v;
    }
    return parse_number(c, ok);
}

static long parse_term(ctx_t *c, int *ok)
{
    long v;

    v = parse_paren_or_num(c, ok);
    if (!*ok)
        return 0;
    while (1) {
        long rhs;
        char op;

        skip_ws(c);
        op = *c->p;
        if (op != '*' && op != '/' && op != '%')
            break;
        c->p += 1;
        rhs = parse_paren_or_num(c, ok);
        if (!*ok)
            return 0;
        if (op == '*') {
            v = v * rhs;
        } else if (op == '/') {
            if (rhs == 0) { *ok = 0; return 0; }
            v = v / rhs;
        } else {
            if (rhs == 0) { *ok = 0; return 0; }
            v = v % rhs;
        }
    }
    return v;
}

static long parse_factor(ctx_t *c, int *ok)
{
    long v;

    v = parse_term(c, ok);
    if (!*ok)
        return 0;
    while (1) {
        long rhs;
        char op;

        skip_ws(c);
        op = *c->p;
        if (op != '+' && op != '-')
            break;
        c->p += 1;
        rhs = parse_term(c, ok);
        if (!*ok)
            return 0;
        if (op == '+')
            v = v + rhs;
        else
            v = v - rhs;
    }
    return v;
}

long eval_expr(const char *s, int *ok)
{
    ctx_t c;
    long v;

    c.p = s;
    *ok = 1;
    v = parse_factor(&c, ok);
    if (!*ok)
        return 0;
    skip_ws(&c);
    if (*c.p != '\0') {
        *ok = 0;
        return 0;
    }
    return v;
}

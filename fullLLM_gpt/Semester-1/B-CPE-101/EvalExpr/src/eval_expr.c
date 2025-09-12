#include <stdlib.h>
#include "../include/eval_expr.h"

static const char *g_p;

static void skip_spaces(void)
{
    while (*g_p == ' ' || *g_p == '\t')
        g_p++;
}

static int parse_number(void)
{
    skip_spaces();
    int val = 0;
    while (*g_p >= '0' && *g_p <= '9') {
        val = val * 10 + (*g_p - '0');
        g_p++;
    }
    return val;
}

static int parse_factor(void)
{
    skip_spaces();
    if (*g_p == '+' || *g_p == '-') {
        int s = (*g_p == '-') ? -1 : 1;
        g_p++;
        int v = parse_factor();
        return s * v;
    }
    if (*g_p == '(') {
        g_p++;
        int v = 0;
        // forward decl
        int parse_expr(void);
        v = parse_expr();
        skip_spaces();
        if (*g_p == ')') g_p++;
        return v;
    }
    return parse_number();
}

static int parse_term(void)
{
    int v = parse_factor();
    for (;;) {
        skip_spaces();
        if (*g_p == '*') { g_p++; v *= parse_factor(); }
        else if (*g_p == '/') { g_p++; int d = parse_factor(); v /= d; }
        else if (*g_p == '%') { g_p++; int d = parse_factor(); v %= d; }
        else break;
    }
    return v;
}

int parse_expr(void)
{
    int v = parse_term();
    for (;;) {
        skip_spaces();
        if (*g_p == '+') { g_p++; v += parse_term(); }
        else if (*g_p == '-') { g_p++; v -= parse_term(); }
        else break;
    }
    return v;
}

int eval_expr(const char *str)
{
    g_p = str;
    int v = parse_expr();
    return v;
}

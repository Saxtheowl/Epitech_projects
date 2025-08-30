/*
** EPITECH PROJECT, 2025
** Bistro_matic_roro
** File description:
** Standalone main compatible with subject main
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "bistro.h"

static int my_strlen_s(const char *s)
{
    int n = 0;
    while (s && s[n]) n += 1;
    return n;
}

static void my_putstr_s(const char *s)
{
    write(1, s, (size_t)my_strlen_s(s));
}

static int my_atoi_s(const char *s)
{
    long v = 0;
    while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); s++; }
    return (int)v;
}

static char *read_len(unsigned int size)
{
    char *expr = malloc(size + 1);
    if (!expr) return NULL;
    if (read(0, expr, size) != (ssize_t)size) { free(expr); return NULL; }
    expr[size] = '\0';
    return expr;
}

int main(int ac, char **av)
{
    char *expr;
    char *res;

    if (ac != 4) {
        my_putstr_s("Usage: "); my_putstr_s(av[0]);
        my_putstr_s(" base ops\"()+-*/%\" exp_len\n");
        return ERR_CODE;
    }
    expr = read_len((unsigned int)my_atoi_s(av[3]));
    if (!expr)
        return ERR_CODE;
    res = eval_expr(av[1], av[2], expr, (unsigned int)strlen(expr));
    free(expr);
    if (!res)
        return ERR_CODE;
    my_putstr_s(res);
    my_putstr_s("\n");
    free(res);
    return 0;
}

/*
** EPITECH PROJECT, 2025
** Wolfram_roro
** File description:
** parse
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "wolfram.h"

static bool match(const char *a, const char *b)
{
    return strcmp(a, b) == 0;
}

static bool parse_opt(int *i, int ac, char const **av, args_t *out)
{
    bool ok;
    const char *arg;
    int val;

    arg = av[*i];
    if (match(arg, "--help"))
        return false;
    if (*i + 1 >= ac)
        return false;
    val = str_to_int(av[*i + 1], &ok);
    if (!ok)
        return false;
    if (match(arg, "--rule"))
        out->rule = val;
    else if (match(arg, "--lines"))
        out->lines = val;
    else if (match(arg, "--start"))
        out->start = val;
    else if (match(arg, "--window"))
        out->window = val;
    else
        return false;
    *i += 1;
    return true;
}

static bool validate(const args_t *cfg)
{
    if (cfg->rule < 0 || cfg->rule > 255)
        return false;
    if (cfg->lines < 0)
        return false;
    if (cfg->start < 0)
        return false;
    if (cfg->window <= 0)
        return false;
    return true;
}

int parse_args(int ac, char const **av, args_t *out)
{
    int i;

    out->rule = -1;
    out->lines = -1;
    out->start = 0;
    out->window = 80;
    if (ac == 2 && strcmp(av[1], "--help") == 0)
        return -1;
    for (i = 1; i < ac; ++i) {
        if (!parse_opt(&i, ac, av, out))
            return 1;
    }
    if (out->rule < 0 || out->lines < 0)
        return 1;
    if (!validate(out))
        return 1;
    return 0;
}

void print_usage(const char *bin)
{
    printf("Usage: %s --rule N --lines N [--start N] [--window N]\n",
        bin);
}


/*
** EPITECH PROJECT, 2025
** Wolfram_roro
** File description:
** parse.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wolfram.h"

static int parse_int(const char *s, int *out)
{
    char *end;
    long v;

    if (!s)
        return 0;
    v = strtol(s, &end, 10);
    if (*s == '\0' || *end != '\0')
        return 0;
    *out = (int)v;
    return 1;
}

static int usage_err(void)
{
    fprintf(stderr, "Usage: wolfram --rule N [--start N] [--lines N] [--window N] [--move N]\n");
    return 84;
}

int parse_args(int ac, char **av, Config *cfg)
{
    int i;
    int v;

    cfg->rule = -1;
    cfg->start = 0;
    cfg->lines = -1;
    cfg->window = 80;
    cfg->move = 0;
    for (i = 1; i < ac; ++i) {
        if (strcmp(av[i], "--help") == 0)
            return usage_err();
        if (strcmp(av[i], "--rule") == 0 && i + 1 < ac && parse_int(av[i+1], &v)) {
            cfg->rule = v; i += 1; continue;
        }
        if (strcmp(av[i], "--start") == 0 && i + 1 < ac && parse_int(av[i+1], &v)) {
            cfg->start = v; i += 1; continue;
        }
        if (strcmp(av[i], "--lines") == 0 && i + 1 < ac && parse_int(av[i+1], &v)) {
            cfg->lines = v; i += 1; continue;
        }
        if (strcmp(av[i], "--window") == 0 && i + 1 < ac && parse_int(av[i+1], &v)) {
            cfg->window = v; i += 1; continue;
        }
        if (strcmp(av[i], "--move") == 0 && i + 1 < ac && parse_int(av[i+1], &v)) {
            cfg->move = v; i += 1; continue;
        }
        return usage_err();
    }
    if (cfg->rule < 0 || cfg->rule > 255 || cfg->window <= 0 ||
        cfg->start < 0 || (cfg->lines != -1 && cfg->lines < 0))
        return usage_err();
    return 0;
}


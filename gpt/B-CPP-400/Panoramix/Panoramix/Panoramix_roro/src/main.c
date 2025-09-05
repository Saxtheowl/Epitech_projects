/*
** EPITECH PROJECT, 2025
** Panoramix_roro
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "panoramix.h"

static int parse_pos(const char *s, int *out)
{
    char *end;
    long v;

    if (!s)
        return 0;
    v = strtol(s, &end, 10);
    if (*s == '\0' || *end != '\0' || v <= 0 || v > 1000000)
        return 0;
    *out = (int)v;
    return 1;
}

static int usage_err(void)
{
    fprintf(stderr, "USAGE: ./panoramix <nb_villagers> <pot_size> <nb_fights> <nb_refills>\n");
    fprintf(stderr, "Values must be >0.\n");
    return 84;
}

int main(int ac, char **av)
{
    int v;
    int p;
    int f;
    int r;

    if (ac != 5)
        return usage_err();
    if (!parse_pos(av[1], &v) || !parse_pos(av[2], &p) ||
        !parse_pos(av[3], &f) || !parse_pos(av[4], &r))
        return usage_err();
    return run_panoramix(v, p, f, r);
}


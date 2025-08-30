/*
** EPITECH PROJECT, 2025
** Rush1_roro
** File description:
** Common main helpers
*/

#include <stdlib.h>
#include "rush.h"

static int parse_int(const char *s, int *out)
{
    char *end;
    long v;

    if (!s || !out)
        return -1;
    v = strtol(s, &end, 10);
    if (end == s || *end != '\0' || v < 0 || v > 100000)
        return -1;
    *out = (int)v;
    return 0;
}

int run_cli(int ac, char **av, pattern_t p)
{
    int w;
    int h;

    if (ac != 3)
        return ERR_CODE;
    if (parse_int(av[1], &w) != 0)
        return ERR_CODE;
    if (parse_int(av[2], &h) != 0)
        return ERR_CODE;
    draw_rect(w, h, p);
    return 0;
}

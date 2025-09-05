/*
** EPITECH PROJECT, 2025
** Panoramix_bootstrap_roro
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "simulation.h"

#ifndef NB_TRAINS
#define NB_TRAINS 3
#endif

#ifndef NB_MAX
#define NB_MAX 1
#endif

static int parse_int(const char *s, int *out)
{
    char *end;
    long v;

    if (!s)
        return 0;
    v = strtol(s, &end, 10);
    if (*s == '\0' || *end != '\0' || v < 1 || v > 1000)
        return 0;
    *out = (int)v;
    return 1;
}

int main(int ac, char **av)
{
    int trains;
    int max;
    int observed;
    bool quiet;

    trains = NB_TRAINS;
    max = NB_MAX;
    quiet = false;
    if (ac >= 2)
        (void)parse_int(av[1], &trains);
    if (ac >= 3)
        (void)parse_int(av[2], &max);
    if (ac >= 4 && av[3][0] == 'q')
        quiet = true;
    if (max < 1)
        max = 1;
    if (max > trains)
        max = trains;
    observed = run_simulation(trains, max, quiet);
    if (!quiet)
        printf("max on bridge: %d\n", observed);
    return 0;
}


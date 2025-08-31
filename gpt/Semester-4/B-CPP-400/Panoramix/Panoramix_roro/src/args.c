/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
**   Argument parsing
*/

#include <stdio.h>
#include "panoramix.h"

void usage(void)
{
    my_dprintf(2, "USAGE: ./panoramix <nb_villagers> <pot_size> <nb_fights> <nb_refills>\n");
}

static void values_err(void)
{
    my_dprintf(2, "Values must be >0.\n");
}

int parse_args(int ac, char **av, sim_t *sim)
{
    int ok = 0;

    if (ac != 5) {
        usage();
        return -1;
    }
    ok = my_atoi_strict(av[1], &sim->nb_villagers);
    ok |= my_atoi_strict(av[2], &sim->pot_size);
    ok |= my_atoi_strict(av[3], &sim->nb_fights);
    ok |= my_atoi_strict(av[4], &sim->nb_refills);
    if (ok != 0 || sim->nb_villagers <= 0 || sim->pot_size <= 0
        || sim->nb_fights <= 0 || sim->nb_refills <= 0) {
        usage();
        values_err();
        return -1;
    }
    return 0;
}


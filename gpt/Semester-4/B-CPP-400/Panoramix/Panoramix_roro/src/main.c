/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
**   Entry point
*/

#include <stdio.h>
#include "panoramix.h"

int main(int ac, char **av)
{
    sim_t sim;

    if (parse_args(ac, av, &sim) != 0)
        return EXIT_ERR;
    if (run_sim(&sim) != 0)
        return EXIT_ERR;
    return 0;
}


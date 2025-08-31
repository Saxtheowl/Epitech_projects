/*
** EPITECH PROJECT, 2025
** Game_of_Stones
** File description:
**   Entry point
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gos.h"

/* no helper needed */

int main(int ac, char **av)
{
    if (ac >= 2) {
        if (gos_strcmp(av[1], "--links") == 0 && ac == 5)
            return run_links_mode(av[2], av[3], av[4]);
        if (gos_strcmp(av[1], "--") == 0 && ac == 6
            && gos_strcmp(av[2], "links") == 0)
            return run_links_mode(av[3], av[4], av[5]);
        if (gos_strcmp(av[1], "--plots") == 0 && ac == 5) {
            int n = atoi(av[4]);
            if (n < 0)
                return GOS_EXIT_ERROR;
            return run_plots_mode(av[2], av[3], n);
        }
        if (gos_strcmp(av[1], "--") == 0 && ac == 7
            && gos_strcmp(av[2], "plots") == 0) {
            int n = atoi(av[6]);
            if (n < 0)
                return GOS_EXIT_ERROR;
            return run_plots_mode(av[3], av[4], n);
        }
    }
    print_usage();
    return GOS_EXIT_ERROR;
}

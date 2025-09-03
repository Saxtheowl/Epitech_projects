/*
** EPITECH PROJECT, 2025
** MyRadar_roro
** File description:
**   Entry point (placeholder)
*/

#include <stdio.h>
#include "radar.h"

static void print_usage(void)
{
    printf("USAGE\n");
    printf("    ./my_radar scenario.txt\n");
}

int radar_main(int ac, char **av)
{
    (void)av;
    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h') {
        print_usage();
        return 0;
    }
    print_usage();
    return 84;
}

int main(int ac, char **av)
{
    return radar_main(ac, av);
}


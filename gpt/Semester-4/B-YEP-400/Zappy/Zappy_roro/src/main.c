/*
** EPITECH PROJECT, 2025
** Zappy_roro
** File description:
**   Entry point (placeholder)
*/

#include <stdio.h>
#include "zappy.h"

static void print_usage(void)
{
    printf("USAGE: ./zappy_roro [options]\n");
}

int zappy_main(int ac, char **av)
{
    (void)av;
    if (ac == 2 && (av[1][0] == '-' && av[1][1] == 'h')) {
        print_usage();
        return 0;
    }
    print_usage();
    return 84;
}

int main(int ac, char **av)
{
    return zappy_main(ac, av);
}


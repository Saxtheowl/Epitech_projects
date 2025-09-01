/*
** EPITECH PROJECT, 2025
** Indie-Studio_roro
** File description:
**   Entry point (placeholder)
*/

#include <stdio.h>
#include "indie.h"

static void print_usage(void)
{
    printf("USAGE: ./indie_studio_roro [options]\n");
}

int indie_main(int ac, char **av)
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
    return indie_main(ac, av);
}


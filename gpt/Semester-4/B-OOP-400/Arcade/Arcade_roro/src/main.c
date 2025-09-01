/*
** EPITECH PROJECT, 2025
** Arcade_roro
** File description:
**   Entry point (placeholder)
*/

#include <stdio.h>
#include "arcade.h"

static void print_usage(void)
{
    printf("USAGE: ./arcade_roro [options]\n");
}

int arcade_main(int ac, char **av)
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
    return arcade_main(ac, av);
}


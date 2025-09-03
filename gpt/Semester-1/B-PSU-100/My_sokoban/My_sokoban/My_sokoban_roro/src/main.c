/*
** EPITECH PROJECT, 2025
** My_sokoban_roro
** File description:
**   Entry point (placeholder)
*/

#include <stdio.h>
#include "sokoban.h"

static void print_usage(void)
{
    printf("USAGE\n");
    printf("    ./my_sokoban map\n");
}

int sokoban_main(int ac, char **av)
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
    return sokoban_main(ac, av);
}


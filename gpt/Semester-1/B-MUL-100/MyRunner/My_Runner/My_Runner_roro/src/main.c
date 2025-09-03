/*
** EPITECH PROJECT, 2025
** My_Runner_roro
** File description:
**   Entry point (placeholder)
*/

#include <stdio.h>
#include "runner.h"

static void print_usage(void)
{
    printf("USAGE\n");
    printf("    ./my_runner [map_file]\n");
}

int runner_main(int ac, char **av)
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
    return runner_main(ac, av);
}


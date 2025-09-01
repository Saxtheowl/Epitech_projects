/*
** EPITECH PROJECT, 2025
** NanoTekSpice_roro
** File description:
**   Entry point (placeholder)
*/

#include <stdio.h>
#include "nanotekspice.h"

static void print_usage(void)
{
    printf("USAGE: ./nanotekspice_roro [options]\n");
}

int nts_main(int ac, char **av)
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
    return nts_main(ac, av);
}


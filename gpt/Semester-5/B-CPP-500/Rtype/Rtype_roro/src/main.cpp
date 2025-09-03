/*
** EPITECH PROJECT, 2025
** Rtype_roro
** File description:
**   Entry point (placeholder)
*/

#include <iostream>
#include "rtype.hpp"

static void print_usage()
{
    std::cout << "USAGE\n";
    std::cout << "    ./rtype_roro [options]\n";
}

int rtype_main(int ac, char **av)
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
    return rtype_main(ac, av);
}


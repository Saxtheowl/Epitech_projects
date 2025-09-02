/*
** EPITECH PROJECT, 2025
** Arcade_roro
** File description:
**   Entry point
*/

#include <iostream>
#include "core.hpp"

static void print_usage()
{
    std::cout << "USAGE: ./arcade <graphlib.so> <gamelib.so>\n";
}

int main(int ac, char **av)
{
    if (ac == 2 && std::string(av[1]) == "-h") { print_usage(); return 0; }
    if (ac != 3) { print_usage(); return 84; }
    Core core;
    return core.run(av[1], av[2]);
}

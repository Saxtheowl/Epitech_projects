/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
**   Args parsing
*/

#include <cstdlib>
#include <cstdio>
#include "plazza.hpp"

bool parse_args(int ac, char **av, Args &out)
{
    if (ac != 4) {
        std::fprintf(stderr, "USAGE: ./plazza <multiplier> <cooks> <restock_ms>\n");
        return false;
    }
    out.multiplier = std::atof(av[1]);
    out.cooks = std::atoi(av[2]);
    out.restock_ms = std::atoi(av[3]);
    if (out.cooks <= 0 || out.restock_ms <= 0 || out.multiplier <= 0.0) {
        std::fprintf(stderr, "Invalid arguments.\n");
        return false;
    }
    return true;
}


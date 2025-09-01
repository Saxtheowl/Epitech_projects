/*
** EPITECH PROJECT, 2025
** Plazza_roro
** File description:
**   Entry point + interactive shell (parser only)
*/

#include <iostream>
#include <string>
#include <vector>
#include "plazza.hpp"
#include "kitchen.hpp"

static void print_usage()
{
    std::cout << "USAGE: ./plazza_roro mult cooks refill_ms\n";
}

extern void reception_loop(const Args &args);

int plazza_main(int ac, char **av)
{
    Args args{};
    if (ac == 2 && std::string(av[1]) == "-h") {
        print_usage();
        return 0;
    }
    if (parse_args(ac, av, args) != 0) {
        print_usage();
        return 84;
    }
    reception_loop(args);
    return 0;
}

int main(int ac, char **av)
{
    return plazza_main(ac, av);
}

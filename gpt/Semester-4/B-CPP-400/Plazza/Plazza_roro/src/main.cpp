/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
**   Entry point
*/

#include "plazza.hpp"

int main(int ac, char **av)
{
    Args args{};
    if (!parse_args(ac, av, args))
        return 84;
    return run_reception(args);
}


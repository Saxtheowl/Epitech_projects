/*
** EPITECH PROJECT, 2025
** Rush1_roro
** File description:
** rush1-2 main
*/

#include "rush.h"

int run_cli(int ac, char **av, pattern_t p);

int main(int ac, char **av)
{
    pattern_t p = { '/', '\\', '\\', '/', '*', '*' };
    return run_cli(ac, av, p);
}

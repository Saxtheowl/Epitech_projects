/*
** EPITECH PROJECT, 2025
** Rush1_roro
** File description:
** rush1-4 main
*/

#include "rush.h"

int run_cli(int ac, char **av, pattern_t p);

int main(int ac, char **av)
{
    pattern_t p = { 'A', 'C', 'A', 'C', 'B', 'B' };
    return run_cli(ac, av, p);
}

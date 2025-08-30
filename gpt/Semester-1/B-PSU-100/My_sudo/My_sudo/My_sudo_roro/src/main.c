/*
** EPITECH PROJECT, 2025
** My_sudo_roro
** File description:
** Main
*/

#include <stdio.h>
#include "sudoku.h"

int main(int ac, char **av)
{
    grid_t g;

    if (ac != 2)
        return ERR_CODE;
    if (load_grid(av[1], &g) != 0)
        return ERR_CODE;
    if (validate_grid(&g) != 0)
        return ERR_CODE;
    if (solve_grid(&g) != 0)
        return ERR_CODE;
    print_grid(&g);
    return 0;
}

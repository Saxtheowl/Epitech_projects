/*
** EPITECH PROJECT, 2025
** My_navy_roro
** File description:
** Main
*/

#include <stdio.h>
#include "navy.h"

int main(int ac, char **av)
{
    game_t g;

    if (ac == 2) {
        if (load_map(av[1], &g.my) != 0)
            return ERR_CODE;
        for (int r = 0; r < 8; ++r)
            for (int c = 0; c < 8; ++c)
                g.enemy.cells[r][c] = '.';
        if (start_connection(&g, NULL) != 0)
            return ERR_CODE;
        return run_game(&g);
    }
    if (ac == 3) {
        if (load_map(av[2], &g.my) != 0)
            return ERR_CODE;
        for (int r = 0; r < 8; ++r)
            for (int c = 0; c < 8; ++c)
                g.enemy.cells[r][c] = '.';
        if (start_connection(&g, av[1]) != 0)
            return ERR_CODE;
        return run_game(&g);
    }
    return ERR_CODE;
}

/*
** EPITECH PROJECT, 2025
** TicTacToe
** File description:
** display
*/

#include "tictactoe.h"

void display_grid(game_t *game)
{
    int i = 0;
    int j = 0;

    printf("+");
    for (j = 0; j < game->size; j++)
        printf(" -");
    printf(" -+\n");
    for (i = 0; i < game->size; i++) {
        printf("|");
        for (j = 0; j < game->size; j++)
            printf(" %c", game->grid[i][j]);
        printf(" |\n");
    }
    printf("+");
    for (j = 0; j < game->size; j++)
        printf(" -");
    printf(" -+\n");
}
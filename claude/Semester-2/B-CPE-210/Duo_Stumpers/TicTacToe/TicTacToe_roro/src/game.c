/*
** EPITECH PROJECT, 2025
** TicTacToe
** File description:
** game
*/

#include "tictactoe.h"

game_t *init_game(args_t *args)
{
    game_t *game = malloc(sizeof(game_t));
    int i = 0;
    int j = 0;

    if (!game)
        return NULL;
    game->size = args->grid_size;
    game->player1_char = args->player1_char;
    game->player2_char = args->player2_char;
    game->current_player = 1;
    game->grid = malloc(game->size * sizeof(char *));
    if (!game->grid) {
        free(game);
        return NULL;
    }
    for (i = 0; i < game->size; i++) {
        game->grid[i] = malloc(game->size * sizeof(char));
        if (!game->grid[i]) {
            for (j = 0; j < i; j++)
                free(game->grid[j]);
            free(game->grid);
            free(game);
            return NULL;
        }
        for (j = 0; j < game->size; j++)
            game->grid[i][j] = ' ';
    }
    return game;
}

void free_game(game_t *game)
{
    int i = 0;

    if (!game)
        return;
    if (game->grid) {
        for (i = 0; i < game->size; i++) {
            if (game->grid[i])
                free(game->grid[i]);
        }
        free(game->grid);
    }
    free(game);
}
/*
** EPITECH PROJECT, 2025
** TicTacToe
** File description:
** logic
*/

#include "tictactoe.h"

int make_move(game_t *game, int x, int y)
{
    char current_char = 0;

    if (game->grid[y][x] != ' ')
        return -1;
    current_char = (game->current_player == 1) ? 
        game->player1_char : game->player2_char;
    game->grid[y][x] = current_char;
    return 0;
}

static int check_line(game_t *game, int row)
{
    int j = 0;
    char first_char = game->grid[row][0];

    if (first_char == ' ')
        return 0;
    for (j = 1; j < game->size; j++) {
        if (game->grid[row][j] != first_char)
            return 0;
    }
    return 1;
}

static int check_column(game_t *game, int col)
{
    int i = 0;
    char first_char = game->grid[0][col];

    if (first_char == ' ')
        return 0;
    for (i = 1; i < game->size; i++) {
        if (game->grid[i][col] != first_char)
            return 0;
    }
    return 1;
}

static int check_diagonals(game_t *game)
{
    int i = 0;
    char first_char = game->grid[0][0];

    if (first_char != ' ') {
        for (i = 1; i < game->size; i++) {
            if (game->grid[i][i] != first_char)
                break;
        }
        if (i == game->size)
            return 1;
    }
    first_char = game->grid[0][game->size - 1];
    if (first_char != ' ') {
        for (i = 1; i < game->size; i++) {
            if (game->grid[i][game->size - 1 - i] != first_char)
                break;
        }
        if (i == game->size)
            return 1;
    }
    return 0;
}

int check_win(game_t *game)
{
    int i = 0;

    for (i = 0; i < game->size; i++) {
        if (check_line(game, i) || check_column(game, i))
            return 1;
    }
    return check_diagonals(game);
}

int is_grid_full(game_t *game)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < game->size; i++) {
        for (j = 0; j < game->size; j++) {
            if (game->grid[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}
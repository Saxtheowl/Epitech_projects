/*
** EPITECH PROJECT, 2024
** Tetris
** File description:
** Piece movement and rotation
*/

#include "../include/tetris.h"

int move_piece(game_t *game, int dx, int dy)
{
    int new_x = game->state.current_x + dx;
    int new_y = game->state.current_y + dy;

    if (can_place_piece(game, new_x, new_y, game->state.current_rotation)) {
        game->state.current_x = new_x;
        game->state.current_y = new_y;
        return 1;
    }

    return 0;
}

int rotate_piece(game_t *game)
{
    int new_rotation = (game->state.current_rotation + 1) % 4;

    if (can_place_piece(game, game->state.current_x, game->state.current_y, new_rotation)) {
        game->state.current_rotation = new_rotation;
        return 1;
    }

    return 0;
}

void drop_piece(game_t *game)
{
    while (move_piece(game, 0, 1)) {
        ;
    }

    place_piece(game);
    spawn_new_piece(game);
}
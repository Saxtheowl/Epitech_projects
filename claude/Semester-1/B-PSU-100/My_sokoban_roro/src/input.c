/*
** EPITECH PROJECT, 2024
** My_sokoban
** File description:
** Input handling for my_sokoban
*/

#include "../include/my_sokoban.h"

void handle_input(game_t *game, int key)
{
    if (game->terminal_too_small)
        return;
    switch (key) {
        case KEY_UP:
            move_player(game, 0, -1);
            break;
        case KEY_DOWN:
            move_player(game, 0, 1);
            break;
        case KEY_LEFT:
            move_player(game, -1, 0);
            break;
        case KEY_RIGHT:
            move_player(game, 1, 0);
            break;
        case ' ':
            reset_game(game, "map");
            break;
        case 'q':
        case 'Q':
        case 27:
            game->game_over = 1;
            break;
    }
    if (check_win_condition(game->map)) {
        game->win = 1;
        game->game_over = 1;
    }
    if (check_lose_condition(game->map)) {
        game->win = 0;
        game->game_over = 1;
    }
}
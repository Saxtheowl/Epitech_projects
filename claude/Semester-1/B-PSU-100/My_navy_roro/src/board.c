/*
** EPITECH PROJECT, 2024
** My_navy
** File description:
** Board management for my_navy
*/

#include "../include/my_navy.h"

void init_boards(game_t *game)
{
    int i, j;

    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            game->my_board[i][j] = '.';
            game->enemy_board[i][j] = '.';
        }
    }
}

void place_ships(game_t *game)
{
    int i, j;
    int x, y, dx, dy;

    for (i = 0; i < NB_SHIPS; i++) {
        dx = game->ships[i].end_x > game->ships[i].start_x ? 1 : -1;
        dy = game->ships[i].end_y > game->ships[i].start_y ? 1 : -1;
        if (game->ships[i].start_x == game->ships[i].end_x)
            dx = 0;
        if (game->ships[i].start_y == game->ships[i].end_y)
            dy = 0;
        x = game->ships[i].start_x;
        y = game->ships[i].start_y;
        for (j = 0; j < game->ships[i].length; j++) {
            game->my_board[y][x] = '0' + game->ships[i].length;
            x += dx;
            y += dy;
        }
    }
}

void display_boards(game_t *game)
{
    int i, j;

    my_putstr("my navy:\n");
    my_putstr("|A B C D E F G H\n");
    my_putstr("-+---------------\n");
    for (i = 0; i < BOARD_SIZE; i++) {
        my_putnbr(i + 1);
        my_putstr("|");
        for (j = 0; j < BOARD_SIZE; j++) {
            my_putchar(game->my_board[i][j]);
            if (j < BOARD_SIZE - 1)
                my_putchar(' ');
        }
        my_putchar('\n');
    }
    my_putstr("enemy navy:\n");
    my_putstr("|A B C D E F G H\n");
    my_putstr("-+---------------\n");
    for (i = 0; i < BOARD_SIZE; i++) {
        my_putnbr(i + 1);
        my_putstr("|");
        for (j = 0; j < BOARD_SIZE; j++) {
            my_putchar(game->enemy_board[i][j]);
            if (j < BOARD_SIZE - 1)
                my_putchar(' ');
        }
        my_putchar('\n');
    }
}
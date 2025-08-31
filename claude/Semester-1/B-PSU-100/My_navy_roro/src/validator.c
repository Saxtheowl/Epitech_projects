/*
** EPITECH PROJECT, 2024
** My_navy
** File description:
** Ship placement validation
*/

#include "../include/my_navy.h"

static int calculate_ship_length(ship_t *ship)
{
    int dx = ship->end_x - ship->start_x;
    int dy = ship->end_y - ship->start_y;

    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    if (dx == 0)
        return dy + 1;
    if (dy == 0)
        return dx + 1;
    return -1;
}

static int validate_ship(ship_t *ship)
{
    int expected_lengths[] = {2, 3, 4, 5};
    int actual_length = calculate_ship_length(ship);
    int i;

    if (actual_length == -1)
        return -1;
    if (actual_length != ship->length)
        return -1;
    for (i = 0; i < NB_SHIPS; i++) {
        if (ship->length == expected_lengths[i])
            return 0;
    }
    return -1;
}

static int check_ship_overlap(game_t *game)
{
    char temp_board[BOARD_SIZE][BOARD_SIZE];
    int i, j, k;
    int x, y, dx, dy;

    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++)
            temp_board[i][j] = '.';
    }
    for (i = 0; i < NB_SHIPS; i++) {
        dx = game->ships[i].end_x > game->ships[i].start_x ? 1 : -1;
        dy = game->ships[i].end_y > game->ships[i].start_y ? 1 : -1;
        if (game->ships[i].start_x == game->ships[i].end_x)
            dx = 0;
        if (game->ships[i].start_y == game->ships[i].end_y)
            dy = 0;
        x = game->ships[i].start_x;
        y = game->ships[i].start_y;
        for (k = 0; k < game->ships[i].length; k++) {
            if (temp_board[y][x] != '.')
                return -1;
            temp_board[y][x] = '0' + game->ships[i].length;
            x += dx;
            y += dy;
        }
    }
    return 0;
}

int validate_ship_placement(game_t *game)
{
    int i;
    int lengths[] = {2, 3, 4, 5};
    int found[NB_SHIPS] = {0};

    for (i = 0; i < NB_SHIPS; i++) {
        if (validate_ship(&game->ships[i]) == -1)
            return -1;
    }
    for (i = 0; i < NB_SHIPS; i++) {
        int j;
        for (j = 0; j < NB_SHIPS; j++) {
            if (game->ships[i].length == lengths[j] && !found[j]) {
                found[j] = 1;
                break;
            }
        }
    }
    for (i = 0; i < NB_SHIPS; i++) {
        if (!found[i])
            return -1;
    }
    return check_ship_overlap(game);
}
/*
** EPITECH PROJECT, 2024
** My_navy
** File description:
** Game initialization and main loop
*/

#include "../include/my_navy.h"

static int establish_connection(game_t *game)
{
    if (game->enemy_pid == 0) {
        my_putstr("my_pid: ");
        my_putnbr(getpid());
        my_putstr("\n");
        my_putstr("waiting for enemy...\n");
        while (game->enemy_pid == 0) {
            pause();
            if (g_game->result_received) {
                game->enemy_pid = g_game->attack_x;
                g_game->result_received = 0;
                break;
            }
        }
        my_putstr("enemy connected\n");
    } else {
        my_putstr("my_pid: ");
        my_putnbr(getpid());
        my_putstr("\n");
        send_position(game->enemy_pid, getpid(), 0);
        my_putstr("successfully connected\n");
    }
    return 0;
}

int start_game(game_t *game)
{
    if (establish_connection(game) == -1)
        return -1;
    game->game_over = 0;
    game->winner = -1;
    while (!game->game_over) {
        if (play_turn(game) == -1)
            return -1;
        if (check_game_over(game))
            break;
        game->turn = !game->turn;
    }
    if (game->winner == 0)
        my_putstr("I won\n");
    else
        my_putstr("Enemy won\n");
    return 0;
}
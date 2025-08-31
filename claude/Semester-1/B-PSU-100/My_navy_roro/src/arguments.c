/*
** EPITECH PROJECT, 2024
** My_navy
** File description:
** Argument parsing for my_navy
*/

#include "../include/my_navy.h"

void print_usage(void)
{
    my_putstr("USAGE\n");
    my_putstr("    ./my_navy [first_player_pid] navy_positions\n");
    my_putstr("DESCRIPTION\n");
    my_putstr("    first_player_pid: only for the 2nd player. ");
    my_putstr("pid of the first player.\n");
    my_putstr("    navy_positions: file representing the ");
    my_putstr("positions of the ships.\n");
}

static int parse_pid(char *pid_str)
{
    int pid = 0;
    int i = 0;

    while (pid_str[i]) {
        if (pid_str[i] < '0' || pid_str[i] > '9')
            return -1;
        pid = pid * 10 + (pid_str[i] - '0');
        i++;
    }
    return pid;
}

int parse_arguments(int argc, char **argv, game_t *game)
{
    if (argc < 2 || argc > 3)
        return -1;
    game->enemy_pid = 0;
    game->turn = 1;
    if (argc == 3) {
        game->enemy_pid = parse_pid(argv[1]);
        if (game->enemy_pid <= 0)
            return -1;
        game->turn = 0;
    }
    return 0;
}
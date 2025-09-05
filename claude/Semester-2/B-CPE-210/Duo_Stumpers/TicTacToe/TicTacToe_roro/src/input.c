/*
** EPITECH PROJECT, 2025
** TicTacToe
** File description:
** input
*/

#include "tictactoe.h"

static int parse_coordinates(char *line, int *x, int *y)
{
    int i = 0;
    int comma_pos = -1;
    char x_str[16];
    char y_str[16];
    int j = 0;

    if (!line)
        return -1;
    while (line[i] && line[i] != '\n') {
        if (line[i] == ',' && comma_pos == -1)
            comma_pos = i;
        i++;
    }
    if (comma_pos == -1 || comma_pos == 0 || comma_pos == i - 1)
        return -1;
    for (j = 0; j < comma_pos && j < 15; j++)
        x_str[j] = line[j];
    x_str[j] = '\0';
    for (j = 0; j < i - comma_pos - 1 && j < 15; j++)
        y_str[j] = line[comma_pos + 1 + j];
    y_str[j] = '\0';
    *x = my_atoi(x_str);
    *y = my_atoi(y_str);
    if (*x < 0 || *y < 0)
        return -1;
    return 0;
}

int get_player_move(game_t *game, int *x, int *y)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_len = 0;

    while (1) {
        printf("Player %d> ", game->current_player);
        read_len = getline(&line, &len, stdin);
        if (read_len == -1) {
            if (line)
                free(line);
            return -1;
        }
        if (parse_coordinates(line, x, y) == 0 && 
            *x >= 0 && *x < game->size && 
            *y >= 0 && *y < game->size) {
            free(line);
            return 0;
        }
    }
    free(line);
    return -1;
}
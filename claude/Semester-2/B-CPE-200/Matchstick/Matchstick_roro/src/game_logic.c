/*
** EPITECH PROJECT, 2024
** Matchstick
** File description:
** Game logic functions
*/

#include "../include/matchstick.h"

int is_game_over(game_t *game)
{
    int i, j;
    int total = 0;

    for (i = 0; i < game->lines; i++) {
        int matches_in_line = count_matches_in_line(i + 1);
        for (j = 0; j < matches_in_line; j++) {
            if (game->board[i][j] == 1)
                total++;
        }
    }
    
    return total == 0;
}

int validate_move(game_t *game, int line, int matches)
{
    int i, available = 0;
    int matches_in_line;

    if (line < 1 || line > game->lines) {
        printf("Error: this line is out of range\n");
        return -1;
    }
    
    if (matches < 1 || matches > game->max_matches) {
        printf("Error: you cannot remove more than %d matches per turn\n", 
               game->max_matches);
        return -1;
    }
    
    matches_in_line = count_matches_in_line(line);
    for (i = matches_in_line - 1; i >= 0; i--) {
        if (game->board[line - 1][i] == 1)
            available++;
    }
    
    if (available == 0) {
        printf("Error: this line is empty\n");
        return -1;
    }
    
    if (matches > available) {
        printf("Error: not enough matches on this line\n");
        return -1;
    }
    
    return 0;
}

int make_move(game_t *game, int line, int matches)
{
    int i, removed = 0;
    int matches_in_line = count_matches_in_line(line);

    for (i = matches_in_line - 1; i >= 0 && removed < matches; i--) {
        if (game->board[line - 1][i] == 1) {
            game->board[line - 1][i] = 0;
            removed++;
        }
    }
    
    return 0;
}
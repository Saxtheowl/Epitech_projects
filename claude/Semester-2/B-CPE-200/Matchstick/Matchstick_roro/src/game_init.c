/*
** EPITECH PROJECT, 2024
** Matchstick
** File description:
** Game initialization and cleanup functions
*/

#include "../include/matchstick.h"

int count_matches_in_line(int line_number)
{
    return 2 * line_number - 1;
}

game_t *init_game(int lines, int max_matches)
{
    game_t *game;
    int i, j;

    game = malloc(sizeof(game_t));
    if (!game)
        return NULL;
        
    game->lines = lines;
    game->max_matches = max_matches;
    game->current_player = 0;
    game->total_matches = 0;
    
    game->board = malloc(sizeof(int *) * lines);
    if (!game->board) {
        free(game);
        return NULL;
    }
    
    for (i = 0; i < lines; i++) {
        int matches_in_line = count_matches_in_line(i + 1);
        game->board[i] = malloc(sizeof(int) * matches_in_line);
        if (!game->board[i]) {
            for (j = 0; j < i; j++)
                free(game->board[j]);
            free(game->board);
            free(game);
            return NULL;
        }
        
        for (j = 0; j < matches_in_line; j++) {
            game->board[i][j] = 1;
        }
        game->total_matches += matches_in_line;
    }
    
    return game;
}

void cleanup_game(game_t *game)
{
    int i;

    if (!game)
        return;
        
    if (game->board) {
        for (i = 0; i < game->lines; i++) {
            if (game->board[i])
                free(game->board[i]);
        }
        free(game->board);
    }
    
    free(game);
}
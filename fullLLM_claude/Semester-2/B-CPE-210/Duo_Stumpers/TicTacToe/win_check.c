#include "tictactoe.h"

static int check_line(game_t *game, int y)
{
    char first = game->grid[y][0];
    int i;
    
    if (first == ' ') {
        return 0;
    }
    
    for (i = 1; i < game->size; i++) {
        if (game->grid[y][i] != first) {
            return 0;
        }
    }
    
    return 1;
}

static int check_column(game_t *game, int x)
{
    char first = game->grid[0][x];
    int i;
    
    if (first == ' ') {
        return 0;
    }
    
    for (i = 1; i < game->size; i++) {
        if (game->grid[i][x] != first) {
            return 0;
        }
    }
    
    return 1;
}

static int check_diagonal1(game_t *game)
{
    char first = game->grid[0][0];
    int i;
    
    if (first == ' ') {
        return 0;
    }
    
    for (i = 1; i < game->size; i++) {
        if (game->grid[i][i] != first) {
            return 0;
        }
    }
    
    return 1;
}

static int check_diagonal2(game_t *game)
{
    char first = game->grid[0][game->size - 1];
    int i;
    
    if (first == ' ') {
        return 0;
    }
    
    for (i = 1; i < game->size; i++) {
        if (game->grid[i][game->size - 1 - i] != first) {
            return 0;
        }
    }
    
    return 1;
}

int check_winner(game_t *game)
{
    int i;
    
    for (i = 0; i < game->size; i++) {
        if (check_line(game, i) || check_column(game, i)) {
            return 1;
        }
    }
    
    if (check_diagonal1(game) || check_diagonal2(game)) {
        return 1;
    }
    
    return 0;
}

int is_grid_full(game_t *game)
{
    int i, j;
    
    for (i = 0; i < game->size; i++) {
        for (j = 0; j < game->size; j++) {
            if (game->grid[i][j] == ' ') {
                return 0;
            }
        }
    }
    
    return 1;
}
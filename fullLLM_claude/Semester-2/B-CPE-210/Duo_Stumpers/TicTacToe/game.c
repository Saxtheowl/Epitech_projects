#include "tictactoe.h"

int init_game(game_t *game)
{
    int i, j;
    
    game->grid = malloc(game->size * sizeof(char *));
    if (!game->grid) {
        return 1;
    }
    
    for (i = 0; i < game->size; i++) {
        game->grid[i] = malloc(game->size * sizeof(char));
        if (!game->grid[i]) {
            for (j = 0; j < i; j++) {
                free(game->grid[j]);
            }
            free(game->grid);
            return 1;
        }
        for (j = 0; j < game->size; j++) {
            game->grid[i][j] = ' ';
        }
    }
    
    return 0;
}

void free_game(game_t *game)
{
    if (game->grid) {
        for (int i = 0; i < game->size; i++) {
            if (game->grid[i]) {
                free(game->grid[i]);
            }
        }
        free(game->grid);
    }
}

void display_grid(game_t *game)
{
    int i, j;
    
    printf("+");
    for (j = 0; j < game->size; j++) {
        printf(" -");
    }
    printf(" +\n");
    
    for (i = 0; i < game->size; i++) {
        printf("|");
        for (j = 0; j < game->size; j++) {
            printf(" %c", game->grid[i][j]);
        }
        printf(" |\n");
    }
    
    printf("+");
    for (j = 0; j < game->size; j++) {
        printf(" -");
    }
    printf(" +\n");
}
#include "tictactoe.h"

int get_move(game_t *game, int *x, int *y)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *comma;
    
    printf("Player %d> ", game->current_player);
    
    nread = getline(&line, &len, stdin);
    if (nread == -1) {
        if (line) {
            free(line);
        }
        return 1;
    }
    
    if (line[nread - 1] == '\n') {
        line[nread - 1] = '\0';
    }
    
    comma = strchr(line, ',');
    if (!comma) {
        free(line);
        return 1;
    }
    
    *comma = '\0';
    *x = atoi(line);
    *y = atoi(comma + 1);
    
    free(line);
    
    if (*x < 0 || *x >= game->size || *y < 0 || *y >= game->size) {
        return 1;
    }
    
    return 0;
}

int make_move(game_t *game, int x, int y)
{
    if (game->grid[y][x] != ' ') {
        return 1;
    }
    
    if (game->current_player == 1) {
        game->grid[y][x] = game->player1_char;
    } else {
        game->grid[y][x] = game->player2_char;
    }
    
    return 0;
}
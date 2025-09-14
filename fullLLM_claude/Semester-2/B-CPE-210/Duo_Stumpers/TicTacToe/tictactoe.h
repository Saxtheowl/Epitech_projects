#ifndef TICTACTOE_H
#define TICTACTOE_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char **grid;
    int size;
    char player1_char;
    char player2_char;
    int current_player;
} game_t;

int parse_args(int ac, char **av, game_t *game);
int init_game(game_t *game);
void free_game(game_t *game);
void display_grid(game_t *game);
int get_move(game_t *game, int *x, int *y);
int make_move(game_t *game, int x, int y);
int check_winner(game_t *game);
int is_grid_full(game_t *game);
void game_loop(game_t *game);

#endif
/*
** EPITECH PROJECT, 2024
** Matchstick
** File description:
** Header file for matchstick game
*/

#ifndef MATCHSTICK_H_
#define MATCHSTICK_H_

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_LINES 100
#define MIN_LINES 2

typedef struct game_s {
    int **board;
    int lines;
    int max_matches;
    int total_matches;
    int current_player;
} game_t;

/* Game initialization and cleanup */
game_t *init_game(int lines, int max_matches);
void cleanup_game(game_t *game);

/* Game display */
void display_board(game_t *game);
void display_line_numbers(int lines);

/* Game logic */
int is_game_over(game_t *game);
int make_move(game_t *game, int line, int matches);
int validate_move(game_t *game, int line, int matches);

/* Player input */
int get_player_line(void);
int get_player_matches(void);

/* AI logic */
void ai_move(game_t *game);
int calculate_nim_sum(game_t *game);

/* Utility functions */
int my_atoi(const char *str);
int count_matches_in_line(int line_number);
void print_usage(void);

/* Error handling */
void print_error(const char *message);
int check_arguments(int argc, char **argv);

#endif /* !MATCHSTICK_H_ */
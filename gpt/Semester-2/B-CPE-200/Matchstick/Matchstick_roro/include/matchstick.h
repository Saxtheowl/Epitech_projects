/*
** EPITECH PROJECT, 2025
** Matchstick
** File description:
** Prototypes
*/

#ifndef MATCHSTICK_H
    #define MATCHSTICK_H

typedef struct {
    int lines;
    int max_remove;
    int width;
    char *grid;
} board_t;

int parse_args(int argc, char **argv, int *lines, int *max_remove);
board_t *board_create(int lines, int max_remove);
void board_destroy(board_t *b);
void board_print(board_t *b);
int count_line_matches(board_t *b, int line);
int remove_matches(board_t *b, int line, int count);
int is_finished(board_t *b);
int player_turn(board_t *b);
int ai_turn(board_t *b);

#endif /* MATCHSTICK_H */


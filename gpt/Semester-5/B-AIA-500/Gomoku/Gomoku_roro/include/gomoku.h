/*
** EPITECH PROJECT, 2025
** Gomoku_roro
** File description:
**   Public interfaces
*/

#ifndef GOMOKU_H
#define GOMOKU_H

#include <stddef.h>

typedef struct gomoku_s {
    int size;
    int last_x;
    int last_y;
    int *cells;
} gomoku_t;

/* entry */
int gomoku_main(int ac, char **av);

/* board */
int board_init(gomoku_t *g, int size);
void board_free(gomoku_t *g);
void board_clear(gomoku_t *g);
int board_idx(const gomoku_t *g, int x, int y);
int board_get(const gomoku_t *g, int x, int y);
int board_set(gomoku_t *g, int x, int y, int who);
int board_in_bounds(const gomoku_t *g, int x, int y);

/* ai */
int ai_pick_move(gomoku_t *g, int *out_x, int *out_y);

/* parser */
int handle_line(gomoku_t *g, const char *line);
void print_usage(void);

/* utils */
char *str_trim(char *s);
int parse_int(const char *s, int *out);
int split_at(const char *s, char sep, char *left, size_t lsz,
    char *right, size_t rsz);

#endif /* GOMOKU_H */

/*
** EPITECH PROJECT, 2025
** Wolfram_roro
** File description:
** wolfram.h
*/

#ifndef WOLFRAM_H
#define WOLFRAM_H

#include <stdbool.h>

typedef struct Config {
    int rule;
    int start;
    int lines;      /* -1 means infinite */
    int window;
    int move;
} Config;

typedef struct Cells {
    int *pos;
    int len;
    int cap;
} Cells;

int parse_args(int ac, char **av, Config *cfg);
void cells_init_single(Cells *c);
void cells_free(Cells *c);
void cells_step(const Cells *cur, Cells *next, int rule);
void print_window(const Cells *c, int window, int move);

#endif /* WOLFRAM_H */


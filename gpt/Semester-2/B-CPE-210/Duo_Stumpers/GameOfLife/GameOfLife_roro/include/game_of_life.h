/*
** EPITECH PROJECT, 2025
** GameOfLife
** File description:
** Prototypes
*/

#ifndef GAME_OF_LIFE_H
    #define GAME_OF_LIFE_H

int parse_int(const char *s, int *out);
int idx(int r, int c, int cols);
int count_neighbors(const char *g, int rows, int cols, int r, int c);
char step_cell(const char *g, int rows, int cols, int r, int c);
void step_grid(const char *in, char *out, int rows, int cols);

#endif /* GAME_OF_LIFE_H */


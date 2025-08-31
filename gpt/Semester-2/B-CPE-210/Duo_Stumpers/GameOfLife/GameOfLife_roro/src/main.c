/*
** EPITECH PROJECT, 2025
** GameOfLife
** File description:
** Main and logic
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_of_life.h"

int parse_int(const char *s, int *out)
{
    char *end;
    long v;

    if (s == NULL || *s == '\0' || out == NULL)
        return 0;
    v = strtol(s, &end, 10);
    if (*end != '\0')
        return 0;
    if (v < 1 || v > 10000)
        return 0;
    *out = (int)v;
    return 1;
}

int idx(int r, int c, int cols)
{
    return r * cols + c;
}

int count_neighbors(const char *g, int rows, int cols, int r, int c)
{
    int dr;
    int dc;
    int rr;
    int cc;
    int n;

    n = 0;
    dr = -1;
    while (dr <= 1) {
        dc = -1;
        while (dc <= 1) {
            if (!(dr == 0 && dc == 0)) {
                rr = r + dr;
                cc = c + dc;
                if (rr >= 0 && rr < rows && cc >= 0 && cc < cols) {
                    if (g[idx(rr, cc, cols)] == 'X')
                        n = n + 1;
                }
            }
            dc = dc + 1;
        }
        dr = dr + 1;
    }
    return n;
}

char step_cell(const char *g, int rows, int cols, int r, int c)
{
    int alive;
    int n;

    alive = (g[idx(r, c, cols)] == 'X');
    n = count_neighbors(g, rows, cols, r, c);
    if (alive && (n == 2 || n == 3))
        return 'X';
    if (!alive && n == 3)
        return 'X';
    return '.';
}

void step_grid(const char *in, char *out, int rows, int cols)
{
    int r;
    int c;

    r = 0;
    while (r < rows) {
        c = 0;
        while (c < cols) {
            out[idx(r, c, cols)] = step_cell(in, rows, cols, r, c);
            c = c + 1;
        }
        r = r + 1;
    }
    out[rows * cols] = '\0';
}

int main(int argc, char **argv)
{
    int rows;
    int cols;
    int steps;
    char *grid;
    char *buf;
    int i;

    if (argc != 5)
        return 84;
    if (!parse_int(argv[1], &rows) || !parse_int(argv[2], &cols) ||
        !parse_int(argv[3], &steps))
        return 84;
    if ((int)strlen(argv[4]) != rows * cols)
        return 84;
    grid = malloc((rows * cols + 1));
    buf = malloc((rows * cols + 1));
    if (!grid || !buf)
        return 84;
    strcpy(grid, argv[4]);
    i = 0;
    while (i < steps) {
        step_grid(grid, buf, rows, cols);
        memcpy(grid, buf, (size_t)(rows * cols + 1));
        i = i + 1;
    }
    printf("%s\n", grid);
    free(grid);
    free(buf);
    return 0;
}


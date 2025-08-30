/*
** EPITECH PROJECT, 2025
** My_sudo_roro
** File description:
** Backtracking Sudoku solver
*/

#include "sudoku.h"

static int can_place(const grid_t *g, int r, int c, char d)
{
    int i;
    int j;
    int br;
    int bc;

    for (i = 0; i < 9; ++i) {
        if (g->cells[r][i] == d)
            return 0;
        if (g->cells[i][c] == d)
            return 0;
    }
    br = (r / 3) * 3;
    bc = (c / 3) * 3;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            if (g->cells[br + i][bc + j] == d)
                return 0;
        }
    }
    return 1;
}

static int find_empty(const grid_t *g, int *rr, int *cc)
{
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (g->cells[r][c] == '.') {
                *rr = r; *cc = c; return 1;
            }
        }
    }
    return 0;
}

static int solve_rec(grid_t *g)
{
    int r;
    int c;

    if (!find_empty(g, &r, &c))
        return 1;
    for (char d = '1'; d <= '9'; ++d) {
        if (can_place(g, r, c, d)) {
            g->cells[r][c] = d;
            if (solve_rec(g))
                return 1;
            g->cells[r][c] = '.';
        }
    }
    return 0;
}

int solve_grid(grid_t *g)
{
    return solve_rec(g) ? 0 : -1;
}

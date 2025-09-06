/*
** EPITECH PROJECT, 2025
** Gomoku_roro
** File description:
**   Board management
*/

#include <stdlib.h>
#include <string.h>
#include "gomoku.h"

int board_init(gomoku_t *g, int size)
{
    size_t n;

    if (!g || size <= 0)
        return 1;
    g->size = size;
    g->last_x = -1;
    g->last_y = -1;
    n = (size_t)size * (size_t)size;
    g->cells = malloc(sizeof(int) * n);
    if (!g->cells)
        return 1;
    memset(g->cells, 0, sizeof(int) * n);
    return 0;
}

void board_free(gomoku_t *g)
{
    if (!g)
        return;
    free(g->cells);
    g->cells = NULL;
    g->size = 0;
}

void board_clear(gomoku_t *g)
{
    size_t n;

    if (!g || !g->cells)
        return;
    n = (size_t)g->size * (size_t)g->size;
    memset(g->cells, 0, sizeof(int) * n);
}

int board_in_bounds(const gomoku_t *g, int x, int y)
{
    return x >= 0 && y >= 0 && x < g->size && y < g->size;
}

int board_idx(const gomoku_t *g, int x, int y)
{
    return y * g->size + x;
}

int board_get(const gomoku_t *g, int x, int y)
{
    if (!board_in_bounds(g, x, y))
        return -1;
    return g->cells[board_idx(g, x, y)];
}

int board_set(gomoku_t *g, int x, int y, int who)
{
    if (!board_in_bounds(g, x, y))
        return 1;
    g->cells[board_idx(g, x, y)] = who;
    g->last_x = x;
    g->last_y = y;
    return 0;
}


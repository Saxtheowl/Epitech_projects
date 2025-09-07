/*
** EPITECH PROJECT, 2025
** Gomoku_roro
** File description:
**   Very simple move chooser
*/

#include "gomoku.h"

static int count_dir(gomoku_t *g, int x, int y, int dx, int dy, int who)
{
    int n;

    n = 0;
    while (board_in_bounds(g, x, y) && board_get(g, x, y) == who) {
        n++;
        x += dx;
        y += dy;
    }
    return n;
}

static int would_win(gomoku_t *g, int x, int y, int who)
{
    int a, b;

    if (board_get(g, x, y) != 0)
        return 0;
    a = count_dir(g, x - 1, y, -1, 0, who) + 1 +
        count_dir(g, x + 1, y, +1, 0, who);
    if (a >= 5)
        return 1;
    b = count_dir(g, x, y - 1, 0, -1, who) + 1 +
        count_dir(g, x, y + 1, 0, +1, who);
    if (b >= 5)
        return 1;
    a = count_dir(g, x - 1, y - 1, -1, -1, who) + 1 +
        count_dir(g, x + 1, y + 1, +1, +1, who);
    if (a >= 5)
        return 1;
    b = count_dir(g, x - 1, y + 1, -1, +1, who) + 1 +
        count_dir(g, x + 1, y - 1, +1, -1, who);
    return b >= 5;
}

static int try_immediate(gomoku_t *g, int who, int *ox, int *oy)
{
    int x, y;

    for (y = 0; y < g->size; ++y)
        for (x = 0; x < g->size; ++x)
            if (would_win(g, x, y, who))
                { *ox = x; *oy = y; return 0; }
    return 1;
}

static int try_center(gomoku_t *g, int *ox, int *oy)
{
    int c;

    c = g->size / 2;
    if (board_get(g, c, c) == 0) {
        *ox = c;
        *oy = c;
        return 0;
    }
    return 1;
}

static int pick_if_free(gomoku_t *g, int x, int y, int *ox, int *oy)
{
    if (!board_in_bounds(g, x, y))
        return 1;
    if (board_get(g, x, y) != 0)
        return 1;
    *ox = x;
    *oy = y;
    return 0;
}

static int try_spiral(gomoku_t *g, int *ox, int *oy)
{
    int c;
    int r;
    int d;

    c = g->size / 2;
    for (r = 0; r < g->size; ++r) {
        for (d = -r; d <= r; ++d) {
            if (pick_if_free(g, c + d, c - r, ox, oy) == 0)
                return 0;
            if (pick_if_free(g, c + d, c + r, ox, oy) == 0)
                return 0;
            if (pick_if_free(g, c - r, c + d, ox, oy) == 0)
                return 0;
            if (pick_if_free(g, c + r, c + d, ox, oy) == 0)
                return 0;
        }
    }
    return 1;
}

int ai_pick_move(gomoku_t *g, int *out_x, int *out_y)
{
    if (try_immediate(g, 1, out_x, out_y) == 0)
        return 0;
    if (try_immediate(g, 2, out_x, out_y) == 0)
        return 0;
    if (try_center(g, out_x, out_y) == 0)
        return 0;
    if (try_spiral(g, out_x, out_y) == 0)
        return 0;
    *out_x = 0;
    *out_y = 0;
    return 0;
}

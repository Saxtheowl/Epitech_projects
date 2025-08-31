/*
** EPITECH PROJECT, 2025
** Tetris
** File description:
** Board functions
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tetris.h"

board_t *board_create(int w, int h)
{
    board_t *b;

    b = malloc(sizeof(board_t));
    if (!b)
        return NULL;
    b->w = w;
    b->h = h;
    b->grid = malloc((size_t)(w * h));
    if (!b->grid) {
        free(b);
        return NULL;
    }
    memset(b->grid, ' ', (size_t)(w * h));
    return b;
}

void board_destroy(board_t *b)
{
    if (!b)
        return;
    free(b->grid);
    free(b);
}

static char get_cell(const board_t *b, int x, int y)
{
    return b->grid[y * b->w + x];
}

static void set_cell(board_t *b, int x, int y, char c)
{
    b->grid[y * b->w + x] = c;
}

void board_print(const board_t *b, const piece_t *p)
{
    int y;
    int x;

    for (y = 0; y < b->h + 2; ++y) {
        if (y == 0 || y == b->h + 1) {
            putchar('+');
            for (x = 0; x < b->w; ++x)
                putchar('-');
            puts("+");
        } else {
            putchar('|');
            for (x = 0; x < b->w; ++x) {
                char c = get_cell(b, x, y - 1);
                if (p) {
                    int px = x - p->x;
                    int py = y - 1 - p->y;
                    if (px >= 0 && px < p->w && py >= 0 && py < p->h &&
                        p->data[py][px] == '#')
                        c = '#';
                }
                putchar(c);
            }
            puts("|");
        }
    }
}

int board_solidify(board_t *b, const piece_t *p)
{
    int y;
    int x;

    for (y = 0; y < p->h; ++y) {
        for (x = 0; x < p->w; ++x) {
            if (p->data[y][x] == '#')
                set_cell(b, p->x + x, p->y + y, '#');
        }
    }
    return 1;
}

int board_clear_lines(board_t *b)
{
    int y;
    int cleared;

    cleared = 0;
    for (y = 0; y < b->h; ++y) {
        int x;
        int full = 1;

        for (x = 0; x < b->w; ++x) {
            if (get_cell(b, x, y) == ' ') {
                full = 0;
                break;
            }
        }
        if (full) {
            memmove(b->grid + b->w, b->grid, (size_t)(y * b->w));
            memset(b->grid, ' ', (size_t)b->w);
            cleared = cleared + 1;
        }
    }
    return cleared;
}


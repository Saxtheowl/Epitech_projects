/*
** EPITECH PROJECT, 2025
** Tetris
** File description:
** Piece functions
*/

#include <string.h>
#include "tetris.h"

void piece_init_I(piece_t *p)
{
    memset(p, 0, sizeof(*p));
    p->w = 4;
    p->h = 1;
    p->data[0][0] = '#';
    p->data[0][1] = '#';
    p->data[0][2] = '#';
    p->data[0][3] = '#';
    p->x = 3;
    p->y = 0;
}

int piece_can_place(const board_t *b, const piece_t *p)
{
    int y;
    int x;

    for (y = 0; y < p->h; ++y) {
        for (x = 0; x < p->w; ++x) {
            if (p->data[y][x] == '#') {
                int gx = p->x + x;
                int gy = p->y + y;
                if (gx < 0 || gx >= b->w || gy < 0 || gy >= b->h)
                    return 0;
                if (b->grid[gy * b->w + gx] != ' ')
                    return 0;
            }
        }
    }
    return 1;
}

void piece_move(piece_t *p, int dx, int dy)
{
    p->x += dx;
    p->y += dy;
}

void piece_rotate(piece_t *p)
{
    char tmp[4][4];
    int x;
    int y;

    memset(tmp, 0, sizeof(tmp));
    for (y = 0; y < p->h; ++y) {
        for (x = 0; x < p->w; ++x)
            tmp[x][p->h - 1 - y] = p->data[y][x];
    }
    memset(p->data, 0, sizeof(p->data));
    for (y = 0; y < p->w; ++y) {
        for (x = 0; x < p->h; ++x)
            p->data[y][x] = tmp[y][x];
    }
    {
        int old_w = p->w;
        p->w = p->h;
        p->h = old_w;
    }
}


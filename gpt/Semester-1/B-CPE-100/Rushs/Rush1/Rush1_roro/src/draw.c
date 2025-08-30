/*
** EPITECH PROJECT, 2025
** Rush1_roro
** File description:
** Rectangle drawing
*/

#include <stdio.h>
#include "rush.h"

static void putn(char ch, int n)
{
    int i;

    for (i = 0; i < n; ++i)
        putchar(ch);
}

static void line(int w, char left, char mid, char right)
{
    if (w <= 0)
        return;
    if (w == 1) {
        putchar(left);
        putchar('\n');
        return;
    }
    putchar(left);
    putn(mid, w - 2);
    putchar(right);
    putchar('\n');
}

int draw_rect(int w, int h, pattern_t p)
{
    int r;

    if (w <= 0 || h <= 0)
        return 0;
    for (r = 0; r < h; ++r) {
        if (r == 0) {
            line(w, p.tl, p.h, p.tr);
        } else if (r == h - 1) {
            line(w, p.bl, p.h, p.br);
        } else {
            line(w, p.v, ' ', p.v);
        }
    }
    return 0;
}

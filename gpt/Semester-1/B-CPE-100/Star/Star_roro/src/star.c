/*
** EPITECH PROJECT, 2025
** Star_roro
** File description:
** Star printing
*/

#include <stdio.h>
#include "star.h"

static void putn(char ch, int n)
{
    int i;

    for (i = 0; i < n; ++i)
        putchar(ch);
}

static int apex_indent(int s)
{
    if (s <= 1)
        return 3;
    return 3 * s - 1;
}

static int band_width(int s)
{
    return 2 * s + 1;
}

static int middle_gap(int s)
{
    if (s <= 1)
        return 1;
    return 2 * s - 3;
}

static void top_cone(int s)
{
    int i;
    int base;

    if (s <= 0)
        return;
    base = apex_indent(s);
    for (i = 0; i < s; ++i) {
        putn(' ', base - i);
        if (i == 0) {
            putchar('*');
        } else {
            putchar('*');
            putn(' ', 2 * i - 1);
            putchar('*');
        }
        putchar('\n');
    }
}

static void band_line(int s)
{
    int bw;
    int gap;

    bw = band_width(s);
    gap = middle_gap(s);
    putn('*', bw);
    putn(' ', gap);
    putn('*', bw);
    putchar('\n');
}

static void diamond(int s)
{
    int d;
    int j;
    int k;
    int gap0;
    int bw;

    d = 2 * s - 1;
    if (d <= 0)
        return;
    bw = band_width(s);
    gap0 = middle_gap(s) + 2 * bw - 4;
    for (j = 0; j < d; ++j) {
        k = j;
        if (k >= s)
            k = d - 1 - j;
        putn(' ', k + 1);
        putchar('*');
        putn(' ', gap0 - 2 * k);
        putchar('*');
        putchar('\n');
    }
}

static void bottom_cones(int s)
{
    int t;
    int inner;
    int base;
    int apex;

    if (s <= 0)
        return;
    base = (s == 1) ? apex_indent(s) : 2 * s;
    apex = apex_indent(s);
    inner = middle_gap(s);
    for (t = 0; t < s; ++t) {
        int cur = inner - 2 * t;

        if (s == 1) {
            putn(' ', apex);
            putchar('*');
            putchar('\n');
            continue;
        }
        if (cur >= 0) {
            putn(' ', base + t);
            putchar('*');
            putn(' ', cur);
            putchar('*');
            putchar('\n');
        } else {
            putn(' ', apex);
            putchar('*');
            putchar('\n');
        }
    }
}

int print_star(int size)
{
    if (size < 0)
        return -1;
    if (size == 0)
        return 0;
    top_cone(size);
    band_line(size);
    diamond(size);
    band_line(size);
    bottom_cones(size);
    return 0;
}

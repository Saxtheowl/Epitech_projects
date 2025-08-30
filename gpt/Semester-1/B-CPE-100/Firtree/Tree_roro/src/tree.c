/*
** EPITECH PROJECT, 2025
** Tree_roro
** File description:
** Firtree printing
*/

#include <stdio.h>

static void putn(char ch, int n)
{
    int i;

    for (i = 0; i < n; ++i)
        putchar(ch);
}

static int trunk_width(int size)
{
    if (size % 2 == 1)
        return size;
    return size + 1;
}

/* total_height kept minimal; removed unused to satisfy -Werror */

static int last_width(int size)
{
    int i;
    int line;
    int stars;
    int cut;

    stars = 1;
    cut = 0;
    for (i = 1; i <= size; ++i) {
        for (line = 0; line < i + 3; ++line)
            stars += 2;
        stars -= 2;
        if (i < size) {
            cut += (i % 2 == 0) ? (i / 2 + 1) : (i / 2 + 1);
            stars -= 2 * cut;
        }
    }
    return stars;
}

int print_tree(int size)
{
    int i;
    int line;
    int stars;
    int cut;
    int width;
    int tw;

    if (size <= 0)
        return 0;
    stars = 1;
    cut = 0;
    for (i = 1; i <= size; ++i) {
        for (line = 0; line < i + 3; ++line) {
            width = last_width(size);
            putn(' ', (width - stars) / 2);
            putchar('/');
            putn('*', stars);
            putchar('\\');
            putchar('\n');
            stars += 2;
        }
        stars -= 2;
        if (i < size) {
            cut += (i % 2 == 0) ? (i / 2 + 1) : (i / 2 + 1);
            stars -= 2 * cut;
        }
    }
    tw = trunk_width(size);
    width = last_width(size);
    for (i = 0; i < size; ++i) {
        putn(' ', (width - tw) / 2);
        putn('|', tw);
        putchar('\n');
    }
    return 0;
}

/*
** EPITECH PROJECT, 2025
** Matchstick
** File description:
** Board management
*/

#include <stdlib.h>
#include <stdio.h>
#include "matchstick.h"

static int compute_width(int lines)
{
    return 2 * lines + 1;
}

board_t *board_create(int lines, int max_remove)
{
    board_t *b;
    int i;
    int w;

    b = malloc(sizeof(board_t));
    if (!b)
        return NULL;
    b->lines = lines;
    b->max_remove = max_remove;
    b->width = compute_width(lines);
    b->grid = malloc((size_t)(b->width * (lines + 2)));
    if (!b->grid) {
        free(b);
        return NULL;
    }
    w = b->width;
    for (i = 0; i < w; ++i) {
        b->grid[i] = '*';
        b->grid[w * (lines + 1) + i] = '*';
    }
    for (i = 1; i <= lines; ++i) {
        int stars = 2 * i - 1;
        int start = (w - stars) / 2;
        int j;

        b->grid[w * i + 0] = '*';
        for (j = 1; j < w - 1; ++j) {
            if (j >= start + 1 && j < start + 1 + stars)
                b->grid[w * i + j] = '|';
            else
                b->grid[w * i + j] = ' ';
        }
        b->grid[w * i + w - 1] = '*';
    }
    return b;
}

void board_destroy(board_t *b)
{
    if (!b)
        return;
    free(b->grid);
    free(b);
}

void board_print(board_t *b)
{
    int i;
    int w;

    w = b->width;
    for (i = 0; i < b->lines + 2; ++i) {
        fwrite(b->grid + i * w, 1, (size_t)w, stdout);
        fputc('\n', stdout);
    }
}

int count_line_matches(board_t *b, int line)
{
    int j;
    int c;
    int w;

    if (line < 1 || line > b->lines)
        return -1;
    w = b->width;
    c = 0;
    for (j = 1; j < w - 1; ++j) {
        if (b->grid[w * line + j] == '|')
            c = c + 1;
    }
    return c;
}

int remove_matches(board_t *b, int line, int count)
{
    int w;
    int j;

    if (line < 1 || line > b->lines || count <= 0)
        return 0;
    if (count > b->max_remove)
        return 0;
    if (count > count_line_matches(b, line))
        return 0;
    w = b->width;
    j = w - 2;
    while (j >= 1 && count > 0) {
        if (b->grid[w * line + j] == '|') {
            b->grid[w * line + j] = ' ';
            count = count - 1;
        }
        j = j - 1;
    }
    return 1;
}

int is_finished(board_t *b)
{
    int i;

    i = 1;
    while (i <= b->lines) {
        if (count_line_matches(b, i) > 0)
            return 0;
        i = i + 1;
    }
    return 1;
}


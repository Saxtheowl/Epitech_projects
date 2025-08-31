/*
** EPITECH PROJECT, 2025
** Dante Solver
** File description:
** Maze parsing
*/

#include <stdlib.h>
#include <string.h>
#include "dante.h"

maze_t *maze_from_string(const char *s)
{
    int w;
    int h;
    int i;
    int j;
    const char *p;
    maze_t *m;

    w = 0;
    p = s;
    while (*p && *p != '\n') {
        w = w + 1;
        p = p + 1;
    }
    h = 0;
    p = s;
    while (*p) {
        if (*p == '\n')
            h = h + 1;
        p = p + 1;
    }
    if (p > s && *(p - 1) != '\n')
        h = h + 1;
    if (w <= 0 || h <= 0)
        return NULL;
    m = malloc(sizeof(maze_t));
    if (!m)
        return NULL;
    m->w = w;
    m->h = h;
    m->cells = malloc((size_t)(w * h));
    if (!m->cells) {
        free(m);
        return NULL;
    }
    i = 0;
    j = 0;
    p = s;
    while (*p) {
        if (*p == '\n') {
            if (j != w) { free(m->cells); free(m); return NULL; }
            j = 0;
            i = i + 1;
        } else {
            m->cells[i * w + j] = *p;
            j = j + 1;
        }
        p = p + 1;
    }
    if (j == w)
        i = i + 1;
    if (i != h) { free(m->cells); free(m); return NULL; }
    return m;
}

void maze_destroy(maze_t *m)
{
    if (!m)
        return;
    free(m->cells);
    free(m);
}


/*
** EPITECH PROJECT, 2025
** Amazed Solver
** File description:
** Maze parsing ('.' free, '#' wall)
*/

#include <stdlib.h>
#include <string.h>
#include "amazed.h"

maze_t *maze_from_string(const char *s)
{
    int w = 0; int h = 0; const char *p = s;
    while (*p && *p != '\n') { w++; p++; }
    p = s; while (*p) { if (*p == '\n') h++; p++; }
    if (p > s && *(p - 1) != '\n') h++;
    if (w <= 0 || h <= 0) return NULL;
    maze_t *m = malloc(sizeof(maze_t)); if (!m) return NULL;
    m->w = w; m->h = h; m->cells = malloc((size_t)(w*h));
    if (!m->cells) { free(m); return NULL; }
    int i = 0; int j = 0; p = s;
    while (*p) {
        if (*p == '\n') { if (j != w) { free(m->cells); free(m); return NULL; } j = 0; i++; }
        else { m->cells[i*w + j] = *p; j++; }
        p++;
    }
    if (j == w) i++;
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

/*
** EPITECH PROJECT, 2025
** Dante Solver
** File description:
** BFS solver
*/

#include <stdlib.h>
#include <string.h>
#include "dante.h"

typedef struct {
    int x;
    int y;
} pt_t;

static int idx(int x, int y, int w) { return y * w + x; }

char *solve_maze(const maze_t *m)
{
    int w = m->w;
    int h = m->h;
    int *prev;
    int *queue;
    int qh;
    int qt;
    char *out;
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    int i;

    if (m->cells[idx(0,0,w)] == 'X' || m->cells[idx(w-1,h-1,w)] == 'X')
        return NULL;
    prev = malloc(sizeof(int) * w * h);
    queue = malloc(sizeof(int) * w * h);
    out = malloc((size_t)(w * h + h));
    if (!prev || !queue || !out) { free(prev); free(queue); free(out); return NULL; }
    for (i = 0; i < w*h; ++i) prev[i] = -2;
    qh = 0; qt = 0;
    queue[qt++] = 0; prev[0] = -1;
    while (qh < qt) {
        int cur = queue[qh++];
        int cx = cur % w;
        int cy = cur / w;
        if (cur == idx(w-1,h-1,w)) break;
        for (i = 0; i < 4; ++i) {
            int nx = cx + dirs[i][0];
            int ny = cy + dirs[i][1];
            int ni;
            if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
            ni = idx(nx, ny, w);
            if (m->cells[ni] == 'X') continue;
            if (prev[ni] != -2) continue;
            prev[ni] = cur;
            queue[qt++] = ni;
        }
    }
    if (prev[idx(w-1,h-1,w)] == -2) { free(prev); free(queue); free(out); return NULL; }
    {
        int cur = idx(w-1,h-1,w);
        char *path = malloc((size_t)(w*h));
        int pc = 0;
        if (!path) { free(prev); free(queue); free(out); return NULL; }
        while (cur != -1) {
            path[pc++] = (char)cur;
            cur = prev[cur];
        }
        /* Build output */
        int x; int y; int k = 0;
        for (y = 0; y < h; ++y) {
            for (x = 0; x < w; ++x) {
                out[k++] = m->cells[idx(x,y,w)];
            }
            out[k++] = '\n';
        }
        out[k-1] = '\0';
        /* mark path with 'o' */
        while (pc--) {
            int pi = (unsigned char)path[pc];
            int px = pi % w; (void)px; /* unused but kept for clarity */
            out[pi + (pi / w)] = 'o';
        }
        free(path);
    }
    free(prev); free(queue);
    return out;
}

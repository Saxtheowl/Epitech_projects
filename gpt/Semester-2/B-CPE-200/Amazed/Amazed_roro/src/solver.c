/*
** EPITECH PROJECT, 2025
** Amazed Solver
** File description:
** BFS solver from S to E (or (0,0) to (w-1,h-1) if not present)
*/

#include <stdlib.h>
#include <string.h>
#include "amazed.h"

static int idx(int x, int y, int w) { return y * w + x; }

char *solve_maze(const maze_t *m)
{
    int w = m->w; int h = m->h;
    int sx = 0, sy = 0, ex = w - 1, ey = h - 1;
    int i;
    for (i = 0; i < w*h; ++i) {
        if (m->cells[i] == 'S') { sy = i / w; sx = i % w; }
        if (m->cells[i] == 'E') { ey = i / w; ex = i % w; }
    }
    if (m->cells[idx(sx,sy,w)] == '#') return NULL;
    if (m->cells[idx(ex,ey,w)] == '#') return NULL;
    int *prev = malloc(sizeof(int) * w*h);
    int *queue = malloc(sizeof(int) * w*h);
    char *out = malloc((size_t)(w*h + h));
    if (!prev || !queue || !out) { free(prev); free(queue); free(out); return NULL; }
    for (i = 0; i < w*h; ++i) prev[i] = -2;
    int qh = 0, qt = 0;
    queue[qt++] = idx(sx,sy,w); prev[idx(sx,sy,w)] = -1;
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    while (qh < qt) {
        int cur = queue[qh++];
        int cx = cur % w, cy = cur / w;
        if (cur == idx(ex,ey,w)) break;
        for (i = 0; i < 4; ++i) {
            int nx = cx + dirs[i][0]; int ny = cy + dirs[i][1];
            if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
            int ni = idx(nx, ny, w);
            if (m->cells[ni] == '#') continue;
            if (prev[ni] != -2) continue;
            prev[ni] = cur; queue[qt++] = ni;
        }
    }
    if (prev[idx(ex,ey,w)] == -2) { free(prev); free(queue); free(out); return NULL; }
    int x, y, k = 0;
    for (y = 0; y < h; ++y) { for (x = 0; x < w; ++x) out[k++] = m->cells[idx(x,y,w)]; out[k++]='\n'; }
    out[k-1] = '\0';
    int cur = idx(ex,ey,w);
    while (cur != -1) { out[cur + (cur / w)] = 'o'; cur = prev[cur]; }
    free(prev); free(queue);
    return out;
}


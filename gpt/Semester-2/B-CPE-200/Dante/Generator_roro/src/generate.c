/*
** EPITECH PROJECT, 2025
** Dante Generator
** File description:
** Perfect maze generator (DFS backtracker) and imperfect tweak
*/

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "generator.h"

static int idx(int x, int y, int w) { return y * w + x; }

static void shuffle_dirs(int dirs[4][2])
{
    int i;

    for (i = 0; i < 4; ++i) {
        int j = rand() % 4;
        int tx = dirs[i][0]; int ty = dirs[i][1];
        dirs[i][0] = dirs[j][0]; dirs[i][1] = dirs[j][1];
        dirs[j][0] = tx; dirs[j][1] = ty;
    }
}

char *generate_maze(int w, int h, int perfect)
{
    int gw = w; int gh = h;
    char *grid = malloc((size_t)(gw * gh));
    int *stack = malloc(sizeof(int) * gw * gh);
    int top = 0;
    int *vis = malloc(sizeof(int) * gw * gh);
    char *out;
    int x; int y; int i;

    if (!grid || !stack || !vis) { free(grid); free(stack); free(vis); return NULL; }
    memset(grid, 'X', (size_t)(gw * gh));
    memset(vis, 0, sizeof(int) * gw * gh);
    x = (w % 2 == 0) ? 0 : 1;
    y = (h % 2 == 0) ? 0 : 1;
    if (x >= gw)
        x = 0;
    if (y >= gh)
        y = 0;
    stack[top++] = idx(x, y, gw);
    vis[idx(x,y,gw)] = 1; grid[idx(x,y,gw)] = '*';
    while (top > 0) {
        int cur = stack[top - 1];
        int cx = cur % gw; int cy = cur / gw;
        int dirs[4][2] = {{2,0},{-2,0},{0,2},{0,-2}};
        int moved = 0;
        shuffle_dirs(dirs);
        for (i = 0; i < 4; ++i) {
            int nx = cx + dirs[i][0]; int ny = cy + dirs[i][1];
            int mx = cx + dirs[i][0] / 2; int my = cy + dirs[i][1] / 2;
            if (nx <= 0 || nx >= gw || ny <= 0 || ny >= gh)
                continue;
            if (vis[idx(nx,ny,gw)])
                continue;
            vis[idx(nx,ny,gw)] = 1;
            grid[idx(mx,my,gw)] = '*';
            grid[idx(nx,ny,gw)] = '*';
            stack[top++] = idx(nx,ny,gw);
            moved = 1;
            break;
        }
        if (!moved)
            top--;
    }
    /* ensure entrance and exit open */
    grid[idx(0,0,gw)] = '*';
    grid[idx(gw-1,gh-1,gw)] = '*';
    if (!perfect) {
        int holes = (gw * gh) / 20 + 1;
        for (i = 0; i < holes; ++i) {
            int rx = rand() % gw; int ry = rand() % gh;
            grid[idx(rx,ry,gw)] = '*';
        }
    }
    out = malloc((size_t)(gw * gh + gh));
    if (!out) { free(grid); free(stack); free(vis); return NULL; }
    {
        int k = 0;
        for (y = 0; y < gh; ++y) {
            for (x = 0; x < gw; ++x) out[k++] = grid[idx(x,y,gw)];
            if (y + 1 < gh) out[k++] = '\n';
        }
        out[k] = '\0';
    }
    free(grid); free(stack); free(vis);
    return out;
}

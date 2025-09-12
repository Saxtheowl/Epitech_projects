#include <stdlib.h>
#include <string.h>
#include "../include/bsq.h"

static int read_int_line(const char *data, size_t len, size_t *pos)
{
    int v = 0; int any = 0;
    while (*pos < len && data[*pos] >= '0' && data[*pos] <= '9') {
        any = 1;
        v = v * 10 + (data[*pos] - '0');
        (*pos)++;
    }
    if (*pos < len && data[*pos] == '\n') (*pos)++;
    return any ? v : -1;
}

int parse_map(const char *data, size_t len, int *rows, int *cols, char **grid)
{
    size_t pos = 0;
    int r = read_int_line(data, len, &pos);
    if (r <= 0) return -1;
    if (pos >= len) return -1;
    // determine cols by first line
    size_t start = pos;
    int c = 0;
    while (pos < len && data[pos] != '\n') { c++; pos++; }
    if (pos < len && data[pos] == '\n') pos++;
    if (c <= 0) return -1;
    // allocate
    char *g = malloc((size_t)r * (size_t)c);
    if (!g) return -1;
    // copy first row
    if ((int)strlen(data + start) < c) { free(g); return -1; }
    for (int j = 0; j < c; ++j) {
        char ch = data[start + j];
        if (ch != '.' && ch != 'o') { free(g); return -1; }
        g[j] = ch;
    }
    // subsequent rows
    for (int i = 1; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (pos >= len) { free(g); return -1; }
            char ch = data[pos++];
            if (ch != '.' && ch != 'o') { free(g); return -1; }
            g[i * c + j] = ch;
        }
        if (pos < len && data[pos] == '\n') pos++;
    }
    *rows = r; *cols = c; *grid = g;
    return 0;
}

void solve_bsq(int rows, int cols, char *grid, square_t *best)
{
    // DP: dp[i][j] size of square ending at i,j
    int *dp = malloc((size_t)rows * (size_t)cols * sizeof(int));
    if (!dp) { best->x = best->y = best->size = 0; return; }
    int bsz = 0, bx = 0, by = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int idx = i*cols + j;
            if (grid[idx] == 'o') { dp[idx] = 0; continue; }
            if (i == 0 || j == 0) dp[idx] = 1;
            else {
                int a = dp[idx - 1];
                int b = dp[idx - cols];
                int c = dp[idx - cols - 1];
                int m = a < b ? a : b; if (c < m) m = c;
                dp[idx] = 1 + m;
            }
            if (dp[idx] > bsz) { bsz = dp[idx]; bx = j; by = i; }
        }
    }
    free(dp);
    best->size = bsz; best->x = bx - bsz + 1; best->y = by - bsz + 1;
}

void mark_square(int rows, int cols, char *grid, square_t best)
{
    for (int i = 0; i < best.size; ++i) {
        for (int j = 0; j < best.size; ++j) {
            int y = best.y + i;
            int x = best.x + j;
            if (y >= 0 && y < rows && x >= 0 && x < cols)
                grid[y*cols + x] = 'x';
        }
    }
}


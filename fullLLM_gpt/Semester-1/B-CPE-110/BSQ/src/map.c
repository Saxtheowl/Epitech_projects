#include <stdlib.h>
#include "../include/bsq.h"

static int parse_int(const char *data, size_t len, size_t *pos)
{
    int value = 0;
    int seen = 0;

    while (*pos < len && data[*pos] >= '0' && data[*pos] <= '9') {
        seen = 1;
        value = value * 10 + (data[*pos] - '0');
        (*pos)++;
    }
    if (!seen)
        return -1;
    if (*pos >= len || data[*pos] != '\n')
        return -1;
    (*pos)++;
    return value;
}

static int parse_first_line(const char *data, size_t len, size_t *pos, int *cols_out)
{
    size_t start = *pos;
    int cols = 0;

    while (*pos < len && data[*pos] != '\n') {
        char ch = data[*pos];
        if (ch != '.' && ch != 'o')
            return -1;
        ++cols;
        ++(*pos);
    }
    if (cols <= 0)
        return -1;
    if (*pos >= len || data[*pos] != '\n')
        return -1;
    ++(*pos);
    *cols_out = cols;
    return (int)start;
}

static int copy_rows(const char *data, size_t len, size_t pos,
                     int rows, int cols, char *grid, size_t start_first_row)
{
    for (int j = 0; j < cols; ++j) {
        char ch = data[start_first_row + j];
        if (ch != '.' && ch != 'o')
            return -1;
        grid[j] = ch;
    }
    for (int row = 1; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (pos >= len)
                return -1;
            char ch = data[pos++];
            if (ch != '.' && ch != 'o')
                return -1;
            grid[row * cols + col] = ch;
        }
        if (pos >= len || data[pos] != '\n')
            return -1;
        ++pos;
    }
    return (pos == len) ? 0 : -1;
}

int parse_map(const char *data, size_t len, int *rows, int *cols, char **grid)
{
    size_t pos = 0;
    int r = parse_int(data, len, &pos);
    if (r <= 0)
        return -1;
    int c = 0;
    int first_row_start = parse_first_line(data, len, &pos, &c);
    if (first_row_start < 0)
        return -1;
    char *map = malloc((size_t)r * (size_t)c);
    if (!map)
        return -1;
    if (copy_rows(data, len, pos, r, c, map, (size_t)first_row_start) != 0) {
        free(map);
        return -1;
    }
    *rows = r;
    *cols = c;
    *grid = map;
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

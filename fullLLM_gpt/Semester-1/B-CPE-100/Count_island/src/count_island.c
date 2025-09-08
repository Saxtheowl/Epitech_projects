#include <stddef.h>
#include "count_island.h"

static int strlen_c(const char *s)
{
    int n = 0; if (!s) return 0; while (s[n]) n++; return n;
}

static void flood(char **map, int rows, int cols, int r, int c, char mark)
{
    if (r < 0 || r >= rows || c < 0 || c >= cols)
        return;
    if (map[r][c] != 'X')
        return;
    map[r][c] = mark;
    flood(map, rows, cols, r-1, c, mark);
    flood(map, rows, cols, r+1, c, mark);
    flood(map, rows, cols, r, c-1, mark);
    flood(map, rows, cols, r, c+1, mark);
}

char **count_island(char **map)
{
    if (!map)
        return map;
    int rows = 0;
    int cols = 0;
    while (map[rows]) rows++;
    if (rows > 0) cols = strlen_c(map[0]);

    int idx = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (map[r][c] == 'X') {
                char mark = (char)('0' + (idx % 10));
                flood(map, rows, cols, r, c, mark);
                idx++;
            }
        }
    }
    return map;
}

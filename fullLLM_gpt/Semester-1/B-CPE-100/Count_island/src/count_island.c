#include <stddef.h>

#include "count_island.h"

static int my_strlen(const char *s)
{
    int len = 0;

    if (s == NULL)
        return 0;
    while (s[len] != '\0')
        ++len;
    return len;
}

static void flood_fill(char **world, int row_count, int row, int col, char mark)
{
    if (row < 0 || row >= row_count)
        return;

    int col_count = my_strlen(world[row]);

    if (col < 0 || col >= col_count)
        return;
    if (world[row][col] != 'X')
        return;

    world[row][col] = mark;

    flood_fill(world, row_count, row - 1, col, mark);
    flood_fill(world, row_count, row + 1, col, mark);
    flood_fill(world, row_count, row, col - 1, mark);
    flood_fill(world, row_count, row, col + 1, mark);
}

int count_island(char **world)
{
    if (world == NULL)
        return 0;

    int rows = 0;

    while (world[rows] != NULL)
        ++rows;
    if (rows == 0)
        return 0;

    int islands = 0;

    for (int r = 0; r < rows; ++r) {
        int cols = my_strlen(world[r]);
        for (int c = 0; c < cols; ++c) {
            if (world[r][c] == 'X') {
                char mark = (islands < 10) ? (char)('0' + islands) : '9';
                flood_fill(world, rows, r, c, mark);
                ++islands;
            }
        }
    }
    return islands;
}

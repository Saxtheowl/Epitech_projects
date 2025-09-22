#include <stdlib.h>
#include <unistd.h>
#include "../include/bsq.h"

static int emit_error(void)
{
    write_all(2, "map error\n", 9);
    return 84;
}

int run_bsq(const char *path)
{
    size_t len = 0;
    char *data = read_entire_file(path, &len);
    if (!data)
        return emit_error();
    int rows = 0;
    int cols = 0;
    char *grid = NULL;
    if (parse_map(data, len, &rows, &cols, &grid) != 0) {
        free(data);
        return emit_error();
    }
    free(data);
    square_t best = {0,0,0};
    if (solve_bsq(rows, cols, grid, &best) != 0) {
        free(grid);
        return emit_error();
    }
    mark_square(rows, cols, grid, best);
    // print
    for (int i = 0; i < rows; ++i) {
        if (write_all(1, grid + i * cols, (size_t)cols) < 0) {
            free(grid);
            return emit_error();
        }
        if (write_all(1, "\n", 1) < 0) {
            free(grid);
            return emit_error();
        }
    }
    free(grid);
    return 0;
}

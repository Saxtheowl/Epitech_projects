#include <stdlib.h>
#include <unistd.h>
#include "../include/bsq.h"

int run_bsq(const char *path)
{
    size_t len = 0; char *data = read_entire_file(path, &len);
    if (!data) return 84;
    int rows=0, cols=0; char *grid=NULL;
    if (parse_map(data, len, &rows, &cols, &grid) != 0) { free(data); return 84; }
    free(data);
    square_t best = {0,0,0};
    solve_bsq(rows, cols, grid, &best);
    mark_square(rows, cols, grid, best);
    // print
    for (int i = 0; i < rows; ++i) {
        if (write_all(1, grid + i*cols, (size_t)cols) < 0) { free(grid); return 84; }
        if (write_all(1, "\n", 1) < 0) { free(grid); return 84; }
    }
    free(grid);
    return 0;
}


#include <stdio.h>
#include <string.h>
#include "../include/sudo.h"

int main(int ac, char **av)
{
    if (ac != 2) { fprintf(stderr, "Usage: %s <grid_file>\n", av[0]); return 84; }
    char g[9][9]; if (read_grid(av[1], g) != 0) return 84;
    if (solve_sudoku(g) != 0) return 84;
    print_grid(g);
    return 0;
}


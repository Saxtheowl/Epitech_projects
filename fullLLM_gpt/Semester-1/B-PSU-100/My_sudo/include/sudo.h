#ifndef SUDO_H
#define SUDO_H

int read_grid(const char *path, char grid[9][9]);
int solve_sudoku(char grid[9][9]);
void print_grid(char grid[9][9]);

#endif


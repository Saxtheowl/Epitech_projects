#include <stdio.h>
#include "../include/sudo.h"

static int is_valid(char grid[9][9], int r, int c, char val)
{
    for (int i=0;i<9;i++) if (grid[r][i]==val || grid[i][c]==val) return 0;
    int br=(r/3)*3, bc=(c/3)*3;
    for (int i=0;i<3;i++) for (int j=0;j<3;j++) if (grid[br+i][bc+j]==val) return 0;
    return 1;
}

static int find_empty(char grid[9][9], int *r, int *c)
{
    for (int i=0;i<9;i++) for (int j=0;j<9;j++) if (grid[i][j]=='.') { *r=i; *c=j; return 1; }
    return 0;
}

static int backtrack(char grid[9][9])
{
    int r,c; if (!find_empty(grid,&r,&c)) return 1;
    for (char v='1'; v<='9'; v++) {
        if (is_valid(grid,r,c,v)) { grid[r][c]=v; if (backtrack(grid)) return 1; grid[r][c]='.'; }
    }
    return 0;
}

int solve_sudoku(char grid[9][9])
{
    return backtrack(grid) ? 0 : 84;
}


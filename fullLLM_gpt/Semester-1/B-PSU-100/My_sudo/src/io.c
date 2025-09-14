#include <stdio.h>
#include <string.h>
#include "../include/sudo.h"

int read_grid(const char *path, char grid[9][9])
{
    FILE *f = fopen(path, "r");
    if (!f) return 84;
    char line[64];
    for (int i=0;i<9;i++) {
        if (!fgets(line, sizeof line, f)) { fclose(f); return 84; }
        int len = (int)strcspn(line, "\r\n");
        if (len != 9) { fclose(f); return 84; }
        for (int j=0;j<9;j++) {
            char c = line[j];
            if (c == '.' || (c>='1' && c<='9')) grid[i][j] = c;
            else { fclose(f); return 84; }
        }
    }
    fclose(f);
    return 0;
}

void print_grid(char grid[9][9])
{
    for (int i=0;i<9;i++) {
        for (int j=0;j<9;j++) putchar(grid[i][j]);
        putchar('\n');
    }
}


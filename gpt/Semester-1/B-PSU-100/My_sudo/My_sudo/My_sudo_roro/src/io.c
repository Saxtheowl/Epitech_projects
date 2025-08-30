/*
** EPITECH PROJECT, 2025
** My_sudo_roro
** File description:
** IO and validation for Sudoku
*/

#include <stdio.h>
#include <string.h>
#include "sudoku.h"

int load_grid(const char *path, grid_t *g)
{
    FILE *fp;
    char line[64];
    int r;

    fp = fopen(path, "r");
    if (!fp)
        return -1;
    for (r = 0; r < 9; ++r) {
        if (!fgets(line, sizeof(line), fp)) { fclose(fp); return -1; }
        if ((int)strlen(line) < 9) { fclose(fp); return -1; }
        for (int c = 0; c < 9; ++c) {
            char ch = line[c];
            if (ch == '.' || (ch >= '1' && ch <= '9'))
                g->cells[r][c] = ch;
            else { fclose(fp); return -1; }
        }
    }
    fclose(fp);
    return 0;
}

static int seen_reset(int seen[10])
{
    for (int i = 0; i < 10; ++i)
        seen[i] = 0;
    return 0;
}

int validate_grid(const grid_t *g)
{
    int seen[10];
    int r;
    int c;

    for (r = 0; r < 9; ++r) {
        seen_reset(seen);
        for (c = 0; c < 9; ++c) {
            char ch = g->cells[r][c];
            if (ch == '.')
                continue;
            if (seen[ch - '0'])
                return -1;
            seen[ch - '0'] = 1;
        }
    }
    for (c = 0; c < 9; ++c) {
        seen_reset(seen);
        for (r = 0; r < 9; ++r) {
            char ch = g->cells[r][c];
            if (ch == '.')
                continue;
            if (seen[ch - '0'])
                return -1;
            seen[ch - '0'] = 1;
        }
    }
    for (r = 0; r < 9; r += 3) {
        for (c = 0; c < 9; c += 3) {
            seen_reset(seen);
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    char ch = g->cells[r + i][c + j];
                    if (ch == '.')
                        continue;
                    if (seen[ch - '0'])
                        return -1;
                    seen[ch - '0'] = 1;
                }
            }
        }
    }
    return 0;
}

void print_grid(const grid_t *g)
{
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c)
            putchar(g->cells[r][c]);
        putchar('\n');
    }
}

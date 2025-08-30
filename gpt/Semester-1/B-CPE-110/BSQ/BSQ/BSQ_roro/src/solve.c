/*
** EPITECH PROJECT, 2025
** BSQ_roro
** File description:
** DP solver
*/

#include <stdlib.h>
#include "bsq.h"

static int min3(int a, int b, int c)
{
    int m;

    m = a;
    if (b < m)
        m = b;
    if (c < m)
        m = c;
    return m;
}

int solve_bsq(map_t *map)
{
    int r;
    int c;
    int best;
    int bi;
    int bj;
    int *dp;

    best = 0;
    bi = 0;
    bj = 0;
    dp = calloc((size_t)(map->cols * map->rows), sizeof(int));
    if (!dp)
        return -1;
    for (r = 0; r < map->rows; ++r) {
        for (c = 0; c < map->cols; ++c) {
            int k = r * map->cols + c;
            if (map->grid[r][c] == 'o') {
                dp[k] = 0;
            } else if (r == 0 || c == 0) {
                dp[k] = 1;
            } else {
                dp[k] = 1 + min3(
                    dp[k - 1],
                    dp[k - map->cols],
                    dp[k - map->cols - 1]
                );
            }
            if (dp[k] > best) {
                best = dp[k];
                bi = r;
                bj = c;
            }
        }
    }
    if (best > 0) {
        int i;
        int j;

        for (i = bi; i > bi - best; --i) {
            for (j = bj; j > bj - best; --j)
                map->grid[i][j] = 'x';
        }
    }
    free(dp);
    return best;
}

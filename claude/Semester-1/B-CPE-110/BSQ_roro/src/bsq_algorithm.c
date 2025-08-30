/*
** EPITECH PROJECT, 2024
** bsq_algorithm.c
** File description:
** BSQ algorithm implementation using dynamic programming
*/

#include <stdlib.h>
#include "../include/bsq.h"

static int min3(int a, int b, int c)
{
    int min_ab = (a < b) ? a : b;
    return (min_ab < c) ? min_ab : c;
}

static int allocate_dp_table(map_t *map)
{
    int i = 0;

    map->dp = malloc(sizeof(int *) * map->rows);
    if (map->dp == NULL)
        return -1;
    while (i < map->rows) {
        map->dp[i] = malloc(sizeof(int) * map->cols);
        if (map->dp[i] == NULL)
            return -1;
        i++;
    }
    return 0;
}

static void init_dp_table(map_t *map)
{
    int i = 0;
    int j = 0;

    while (i < map->rows) {
        j = 0;
        while (j < map->cols) {
            if (map->grid[i][j] == 'o') {
                map->dp[i][j] = 0;
            } else {
                map->dp[i][j] = 1;
            }
            j++;
        }
        i++;
    }
}

static void compute_dp_table(map_t *map)
{
    int i = 1;
    int j = 1;

    while (i < map->rows) {
        j = 1;
        while (j < map->cols) {
            if (map->grid[i][j] == '.') {
                map->dp[i][j] = min3(map->dp[i-1][j],
                                     map->dp[i][j-1],
                                     map->dp[i-1][j-1]) + 1;
            }
            j++;
        }
        i++;
    }
}

square_t find_biggest_square(map_t *map)
{
    square_t square = {0, 0, 0};
    int i = 0;
    int j = 0;

    if (map == NULL || allocate_dp_table(map) == -1)
        return square;
    
    init_dp_table(map);
    compute_dp_table(map);
    
    while (i < map->rows) {
        j = 0;
        while (j < map->cols) {
            if (map->dp[i][j] > square.size) {
                square.size = map->dp[i][j];
                square.row = i - square.size + 1;
                square.col = j - square.size + 1;
            }
            j++;
        }
        i++;
    }
    
    return square;
}
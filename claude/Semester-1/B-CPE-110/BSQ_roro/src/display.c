/*
** EPITECH PROJECT, 2024
** display.c
** File description:
** Display and cleanup functions for BSQ
*/

#include <stdlib.h>
#include "../include/bsq.h"

void print_result(map_t *map, square_t square)
{
    int i = 0;
    int j = 0;

    if (map == NULL || map->grid == NULL)
        return;
    
    while (i < map->rows) {
        j = 0;
        while (j < map->cols) {
            if (i >= square.row && i < square.row + square.size &&
                j >= square.col && j < square.col + square.size) {
                my_putchar('x');
            } else {
                my_putchar(map->grid[i][j]);
            }
            j++;
        }
        my_putchar('\n');
        i++;
    }
}

void free_map(map_t *map)
{
    int i = 0;

    if (map == NULL)
        return;
    
    if (map->grid) {
        while (i < map->rows) {
            if (map->grid[i])
                free(map->grid[i]);
            i++;
        }
        free(map->grid);
    }
    
    if (map->dp) {
        i = 0;
        while (i < map->rows) {
            if (map->dp[i])
                free(map->dp[i]);
            i++;
        }
        free(map->dp);
    }
}
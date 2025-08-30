/*
** EPITECH PROJECT, 2024
** count_island.c
** File description:
** main function to count islands in a 2D grid
*/

#include "../include/count_island.h"

int count_island(char **world)
{
    int height = 0;
    int width = 0;
    int island_count = 0;
    int row = 0;
    int col = 0;

    if (world == NULL)
        return 0;
    height = get_grid_height(world);
    if (height == 0)
        return 0;
    for (row = 0; row < height; row++) {
        width = get_grid_width(world, row);
        for (col = 0; col < width; col++) {
            if (world[row][col] == 'X') {
                flood_fill(world, row, col, '0' + island_count);
                island_count++;
            }
        }
    }
    return island_count;
}
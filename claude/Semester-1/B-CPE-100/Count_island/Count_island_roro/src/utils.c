/*
** EPITECH PROJECT, 2024
** utils.c
** File description:
** utility functions for count_island
*/

#include "../include/count_island.h"

int get_grid_height(char **world)
{
    int height = 0;

    if (world == NULL)
        return 0;
    while (world[height] != NULL)
        height++;
    return height;
}

int get_grid_width(char **world, int row)
{
    if (world == NULL || world[row] == NULL)
        return 0;
    return my_strlen(world[row]);
}

int is_valid_position(char **world, int row, int col)
{
    int height = get_grid_height(world);
    int width = 0;

    if (world == NULL || row < 0 || col < 0)
        return 0;
    if (row >= height)
        return 0;
    width = get_grid_width(world, row);
    if (col >= width)
        return 0;
    return 1;
}
/*
** EPITECH PROJECT, 2024
** flood_fill.c
** File description:
** flood fill algorithm for marking islands
*/

#include "../include/count_island.h"

void flood_fill(char **world, int row, int col, char island_id)
{
    if (!is_valid_position(world, row, col))
        return;
    if (world[row][col] != 'X')
        return;
    world[row][col] = island_id;
    flood_fill(world, row - 1, col, island_id);
    flood_fill(world, row + 1, col, island_id);
    flood_fill(world, row, col - 1, island_id);
    flood_fill(world, row, col + 1, island_id);
}
/*
** EPITECH PROJECT, 2024
** Count_island
** File description:
** Count island using flood fill algorithm
*/

#include "include/my.h"

int is_valid_position(char **world, int x, int y, int rows, int cols)
{
    if (x < 0 || x >= rows || y < 0 || y >= cols)
        return 0;
    return (world[x][y] == 'X');
}

void flood_fill(char **world, int x, int y, int rows, int cols, int island_id)
{
    if (!is_valid_position(world, x, y, rows, cols))
        return;
    
    world[x][y] = '0' + (island_id % 10);
    
    flood_fill(world, x - 1, y, rows, cols, island_id);
    flood_fill(world, x + 1, y, rows, cols, island_id);
    flood_fill(world, x, y - 1, rows, cols, island_id);
    flood_fill(world, x, y + 1, rows, cols, island_id);
}

int count_island(char **world)
{
    int i = 0;
    int j = 0;
    int rows;
    int cols;
    int island_count = 0;
    
    if (!world || !world[0])
        return 0;
    
    rows = 0;
    while (world[rows])
        rows++;
    
    cols = my_strlen(world[0]);
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (world[i][j] == 'X') {
                flood_fill(world, i, j, rows, cols, island_count);
                island_count++;
            }
        }
    }
    
    return island_count;
}
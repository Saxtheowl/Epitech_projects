#include "my.h"

static void mark_island(char **world, int row, int col, char island_num)
{
    if (world[row] == 0 || world[row][col] != 'X')
        return;
    
    world[row][col] = island_num;
    
    if (col > 0)
        mark_island(world, row, col - 1, island_num);
    if (world[row][col + 1] != '\0')
        mark_island(world, row, col + 1, island_num);
    if (row > 0)
        mark_island(world, row - 1, col, island_num);
    if (world[row + 1] != 0)
        mark_island(world, row + 1, col, island_num);
}

int count_island(char **world)
{
    int island_count = 0;
    int row = 0;
    int col;
    
    if (world == 0)
        return 0;
    
    while (world[row] != 0) {
        col = 0;
        while (world[row][col] != '\0') {
            if (world[row][col] == 'X') {
                mark_island(world, row, col, '0' + island_count);
                island_count++;
            }
            col++;
        }
        row++;
    }
    
    return island_count;
}
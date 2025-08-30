/*
** EPITECH PROJECT, 2025
** Count_island_roro
** File description:
** Island labeling
*/

#include "count_island.h"

static void flood(map_t *map, int r, int c, char label)
{
    if (r < 0 || c < 0)
        return;
    if (r >= map->rows || c >= map->cols)
        return;
    if (map->grid[r][c] != 'X')
        return;
    map->grid[r][c] = label;
    flood(map, r + 1, c, label);
    flood(map, r - 1, c, label);
    flood(map, r, c + 1, label);
    flood(map, r, c - 1, label);
}

char label_for(int index)
{
    if (index < 10)
        return (char)('0' + index);
    index -= 10;
    if (index < 26)
        return (char)('a' + index);
    index -= 26;
    if (index < 26)
        return (char)('A' + index);
    return '*';
}

int label_islands(map_t *map)
{
    int r;
    int c;
    int count;
    char lab;

    count = 0;
    for (r = 0; r < map->rows; ++r) {
        for (c = 0; c < map->cols; ++c) {
            if (map->grid[r][c] == 'X') {
                lab = label_for(count);
                flood(map, r, c, lab);
                count += 1;
            }
        }
    }
    return count;
}


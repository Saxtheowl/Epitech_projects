/*
** EPITECH PROJECT, 2024
** My_sokoban
** File description:
** Win/lose condition checking for my_sokoban
*/

#include "../include/my_sokoban.h"

int check_win_condition(map_t *map)
{
    update_box_storage_count(map);
    return (map->boxes_on_storage == map->boxes_count);
}

static int can_box_be_moved(map_t *map, int x, int y)
{
    if (map->grid[y][x] != BOX && map->grid[y][x] != BOX_ON_STORAGE)
        return 0;
    if (can_move_to(map, x - 1, y) || can_move_to(map, x + 1, y) ||
        can_move_to(map, x, y - 1) || can_move_to(map, x, y + 1))
        return 1;
    return 0;
}

static int is_box_in_corner(map_t *map, int x, int y)
{
    if (map->grid[y][x] != BOX)
        return 0;
    if ((map->grid[y - 1][x] == WALL || map->grid[y + 1][x] == WALL) &&
        (map->grid[y][x - 1] == WALL || map->grid[y][x + 1] == WALL))
        return 1;
    return 0;
}

int check_lose_condition(map_t *map)
{
    int i, j;
    int movable_boxes = 0;

    for (i = 0; i < map->height; i++) {
        for (j = 0; j < map->width; j++) {
            if (map->grid[i][j] == BOX || map->grid[i][j] == BOX_ON_STORAGE) {
                if (can_box_be_moved(map, j, i))
                    movable_boxes++;
                if (is_box_in_corner(map, j, i) && map->grid[i][j] == BOX)
                    return 1;
            }
        }
    }
    return (movable_boxes == 0 && !check_win_condition(map));
}
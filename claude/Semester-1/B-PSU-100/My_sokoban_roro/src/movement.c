/*
** EPITECH PROJECT, 2024
** My_sokoban
** File description:
** Player and box movement logic for my_sokoban
*/

#include "../include/my_sokoban.h"

int can_move_to(map_t *map, int x, int y)
{
    if (x < 0 || x >= map->width || y < 0 || y >= map->height)
        return 0;
    if (map->grid[y][x] == WALL)
        return 0;
    if (map->grid[y][x] == BOX || map->grid[y][x] == BOX_ON_STORAGE)
        return 0;
    return 1;
}

int can_push_box(map_t *map, int x, int y, int dx, int dy)
{
    int new_x = x + dx;
    int new_y = y + dy;

    if (new_x < 0 || new_x >= map->width || new_y < 0 || new_y >= map->height)
        return 0;
    if (map->grid[new_y][new_x] == WALL)
        return 0;
    if (map->grid[new_y][new_x] == BOX || map->grid[new_y][new_x] == BOX_ON_STORAGE)
        return 0;
    return 1;
}

void push_box(map_t *map, int from_x, int from_y, int to_x, int to_y)
{
    char old_box = map->grid[from_y][from_x];
    char new_pos = map->grid[to_y][to_x];

    if (old_box == BOX_ON_STORAGE)
        map->grid[from_y][from_x] = STORAGE;
    else
        map->grid[from_y][from_x] = EMPTY;
    if (new_pos == STORAGE)
        map->grid[to_y][to_x] = BOX_ON_STORAGE;
    else
        map->grid[to_y][to_x] = BOX;
    update_box_storage_count(map);
}

int move_player(game_t *game, int dx, int dy)
{
    map_t *map = game->map;
    int new_x = map->player_pos.x + dx;
    int new_y = map->player_pos.y + dy;
    char current_player = map->grid[map->player_pos.y][map->player_pos.x];
    char target = map->grid[new_y][new_x];

    if (new_x < 0 || new_x >= map->width || new_y < 0 || new_y >= map->height)
        return 0;
    if (target == WALL)
        return 0;
    if (target == BOX || target == BOX_ON_STORAGE) {
        if (!can_push_box(map, new_x, new_y, dx, dy))
            return 0;
        push_box(map, new_x, new_y, new_x + dx, new_y + dy);
    }
    if (current_player == PLAYER_ON_STORAGE)
        map->grid[map->player_pos.y][map->player_pos.x] = STORAGE;
    else
        map->grid[map->player_pos.y][map->player_pos.x] = EMPTY;
    if (map->grid[new_y][new_x] == STORAGE)
        map->grid[new_y][new_x] = PLAYER_ON_STORAGE;
    else
        map->grid[new_y][new_x] = PLAYER;
    map->player_pos.x = new_x;
    map->player_pos.y = new_y;
    return 1;
}
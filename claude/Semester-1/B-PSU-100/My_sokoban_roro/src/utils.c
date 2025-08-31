/*
** EPITECH PROJECT, 2024
** My_sokoban
** File description:
** Utility functions for my_sokoban testing
*/

#include "../include/my_sokoban.h"

position_t *get_player_position(map_t *map)
{
    position_t *pos = malloc(sizeof(position_t));

    if (!pos)
        return NULL;
    pos->x = map->player_pos.x;
    pos->y = map->player_pos.y;
    return pos;
}

static char **allocate_map(int width, int height)
{
    char **grid = malloc(sizeof(char *) * height);
    int i;

    if (!grid)
        return NULL;
    for (i = 0; i < height; i++) {
        grid[i] = malloc(sizeof(char) * (width + 1));
        if (!grid[i]) {
            while (i > 0)
                free(grid[--i]);
            free(grid);
            return NULL;
        }
        memset(grid[i], ' ', width);
        grid[i][width] = '\0';
    }
    return grid;
}

map_t *make_map_from_string(const char *map_str)
{
    map_t *map;
    int i, line, col;
    int lines = 0;
    int max_width = 0;
    int current_width = 0;

    if (!map_str)
        return NULL;
    for (i = 0; map_str[i]; i++) {
        if (map_str[i] == '\n') {
            lines++;
            if (current_width > max_width)
                max_width = current_width;
            current_width = 0;
        } else {
            current_width++;
        }
    }
    if (current_width > max_width)
        max_width = current_width;
    if (current_width > 0)
        lines++;
    map = malloc(sizeof(map_t));
    if (!map)
        return NULL;
    map->width = max_width;
    map->height = lines;
    map->grid = allocate_map(max_width, lines);
    if (!map->grid) {
        free(map);
        return NULL;
    }
    line = 0;
    col = 0;
    for (i = 0; map_str[i]; i++) {
        if (map_str[i] == '\n') {
            line++;
            col = 0;
        } else {
            map->grid[line][col] = map_str[i];
            if (map_str[i] == PLAYER) {
                map->player_pos.x = col;
                map->player_pos.y = line;
            }
            col++;
        }
    }
    update_box_storage_count(map);
    return map;
}
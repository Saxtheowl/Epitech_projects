/*
** EPITECH PROJECT, 2024
** My_sokoban
** File description:
** Map validation for my_sokoban
*/

#include "../include/my_sokoban.h"

static int is_valid_char(char c)
{
    return (c == WALL || c == EMPTY || c == PLAYER || c == BOX || 
            c == STORAGE || c == PLAYER_ON_STORAGE || c == BOX_ON_STORAGE);
}

static int validate_characters(map_t *map)
{
    int i, j;

    for (i = 0; i < map->height; i++) {
        for (j = 0; j < map->width; j++) {
            if (!is_valid_char(map->grid[i][j])) {
                fprintf(stderr, "Error: Invalid character in map\n");
                return -1;
            }
        }
    }
    return 0;
}

static int count_players(map_t *map)
{
    int i, j;
    int player_count = 0;

    for (i = 0; i < map->height; i++) {
        for (j = 0; j < map->width; j++) {
            if (map->grid[i][j] == PLAYER || 
                map->grid[i][j] == PLAYER_ON_STORAGE)
                player_count++;
        }
    }
    return player_count;
}

int count_char_in_map(map_t *map, char c)
{
    int i, j;
    int count = 0;

    for (i = 0; i < map->height; i++) {
        for (j = 0; j < map->width; j++) {
            if (map->grid[i][j] == c)
                count++;
        }
    }
    return count;
}

void update_box_storage_count(map_t *map)
{
    map->boxes_count = count_char_in_map(map, BOX) + 
                       count_char_in_map(map, BOX_ON_STORAGE);
    map->storages_count = count_char_in_map(map, STORAGE) + 
                          count_char_in_map(map, BOX_ON_STORAGE) +
                          count_char_in_map(map, PLAYER_ON_STORAGE);
    map->boxes_on_storage = count_char_in_map(map, BOX_ON_STORAGE);
}

int validate_map(map_t *map)
{
    int player_count;

    if (validate_characters(map) == -1)
        return -1;
    player_count = count_players(map);
    if (player_count != 1) {
        fprintf(stderr, "Error: Map must contain exactly one player\n");
        return -1;
    }
    if (count_char_in_map(map, BOX) + count_char_in_map(map, BOX_ON_STORAGE) == 0) {
        fprintf(stderr, "Error: Map must contain at least one box\n");
        return -1;
    }
    if (count_char_in_map(map, STORAGE) + count_char_in_map(map, BOX_ON_STORAGE) +
        count_char_in_map(map, PLAYER_ON_STORAGE) == 0) {
        fprintf(stderr, "Error: Map must contain at least one storage location\n");
        return -1;
    }
    return 0;
}
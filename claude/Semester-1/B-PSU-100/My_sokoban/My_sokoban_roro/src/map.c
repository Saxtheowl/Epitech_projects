/*
** EPITECH PROJECT, 2025
** my_sokoban
** File description:
** Map loading and management functions
*/

#include "sokoban.h"
#include <stdio.h>
#include <string.h>

static char *read_file_content(const char *filename)
{
    FILE *file = fopen(filename, "r");
    char *content = NULL;
    size_t size = 0;
    char *line = NULL;
    size_t line_size = 0;
    
    if (file == NULL)
        return NULL;
    
    while (getline(&line, &line_size, file) != -1) {
        size_t old_size = size;
        size += strlen(line);
        content = realloc(content, size + 1);
        if (content == NULL) {
            free(line);
            fclose(file);
            return NULL;
        }
        if (old_size == 0)
            content[0] = '\0';
        strcat(content, line);
    }
    
    free(line);
    fclose(file);
    return content;
}

static int count_lines(const char *content)
{
    int lines = 0;
    
    if (content == NULL)
        return 0;
    
    for (int i = 0; content[i] != '\0'; i++) {
        if (content[i] == '\n')
            lines++;
    }
    
    if (strlen(content) > 0 && content[strlen(content) - 1] != '\n')
        lines++;
    
    return lines;
}

static int get_max_width(const char *content)
{
    int max_width = 0;
    int current_width = 0;
    
    for (int i = 0; content[i] != '\0'; i++) {
        if (content[i] == '\n') {
            if (current_width > max_width)
                max_width = current_width;
            current_width = 0;
        } else {
            current_width++;
        }
    }
    
    if (current_width > max_width)
        max_width = current_width;
    
    return max_width;
}

sokoban_map_t *make_map_from_string(const char *map_string)
{
    sokoban_map_t *map;
    int line = 0, col = 0;
    
    if (map_string == NULL)
        return NULL;
    
    map = malloc(sizeof(sokoban_map_t));
    if (map == NULL)
        return NULL;
    
    map->height = count_lines(map_string);
    map->width = get_max_width(map_string);
    map->boxes_count = 0;
    map->targets_count = 0;
    
    map->grid = malloc(sizeof(char *) * (map->height + 1));
    if (map->grid == NULL) {
        free(map);
        return NULL;
    }
    
    for (int i = 0; i < map->height; i++) {
        map->grid[i] = malloc(sizeof(char) * (map->width + 1));
        if (map->grid[i] == NULL) {
            for (int j = 0; j < i; j++)
                free(map->grid[j]);
            free(map->grid);
            free(map);
            return NULL;
        }
        memset(map->grid[i], ' ', map->width);
        map->grid[i][map->width] = '\0';
    }
    map->grid[map->height] = NULL;
    
    for (int i = 0; map_string[i] != '\0'; i++) {
        if (map_string[i] == '\n') {
            line++;
            col = 0;
        } else {
            if (line < map->height && col < map->width) {
                map->grid[line][col] = map_string[i];
                if (map_string[i] == PLAYER) {
                    map->player_pos.x = col;
                    map->player_pos.y = line;
                }
                if (map_string[i] == BOX)
                    map->boxes_count++;
                if (map_string[i] == TARGET)
                    map->targets_count++;
            }
            col++;
        }
    }
    
    return map;
}

sokoban_map_t *load_map_from_file(const char *filename)
{
    char *content;
    sokoban_map_t *map;
    
    if (filename == NULL)
        return NULL;
    
    content = read_file_content(filename);
    if (content == NULL)
        return NULL;
    
    map = make_map_from_string(content);
    free(content);
    
    return map;
}

void free_map(sokoban_map_t *map)
{
    if (map == NULL)
        return;
    
    if (map->grid != NULL) {
        for (int i = 0; i < map->height; i++) {
            if (map->grid[i] != NULL)
                free(map->grid[i]);
        }
        free(map->grid);
    }
    free(map);
}

int validate_map(sokoban_map_t *map)
{
    int player_count = 0;
    
    if (map == NULL || map->grid == NULL)
        return 0;
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            char c = map->grid[y][x];
            if (c != WALL && c != PLAYER && c != BOX && c != TARGET && c != EMPTY)
                return 0;
            if (c == PLAYER)
                player_count++;
        }
    }
    
    return (player_count == 1 && map->boxes_count > 0 && map->targets_count > 0);
}

position_t *get_player_position(sokoban_map_t *map)
{
    position_t *pos;
    
    if (map == NULL)
        return NULL;
    
    pos = malloc(sizeof(position_t));
    if (pos == NULL)
        return NULL;
    
    pos->x = map->player_pos.x;
    pos->y = map->player_pos.y;
    
    return pos;
}
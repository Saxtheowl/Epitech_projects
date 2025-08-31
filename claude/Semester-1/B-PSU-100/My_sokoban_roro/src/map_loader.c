/*
** EPITECH PROJECT, 2024
** My_sokoban
** File description:
** Map loading and validation for my_sokoban
*/

#include "../include/my_sokoban.h"

static int get_map_dimensions(FILE *file, int *width, int *height)
{
    char *line = NULL;
    size_t len = 0;
    int line_width;

    *width = 0;
    *height = 0;
    while (getline(&line, &len, file) != -1) {
        line_width = strlen(line);
        if (line[line_width - 1] == '\n')
            line_width--;
        if (line_width > *width)
            *width = line_width;
        (*height)++;
    }
    free(line);
    rewind(file);
    return 0;
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

static int load_map_content(FILE *file, map_t *map)
{
    char *line = NULL;
    size_t len = 0;
    int row = 0;
    int i;

    while (getline(&line, &len, file) != -1 && row < map->height) {
        for (i = 0; i < (int)strlen(line) && i < map->width; i++) {
            if (line[i] == '\n')
                break;
            map->grid[row][i] = line[i];
            if (line[i] == PLAYER) {
                map->player_pos.x = i;
                map->player_pos.y = row;
            }
        }
        row++;
    }
    free(line);
    return 0;
}

map_t *load_map(char *filename)
{
    FILE *file = fopen(filename, "r");
    map_t *map;

    if (!file) {
        fprintf(stderr, "Error: Cannot open map file\n");
        return NULL;
    }
    map = malloc(sizeof(map_t));
    if (!map) {
        fclose(file);
        return NULL;
    }
    if (get_map_dimensions(file, &map->width, &map->height) == -1) {
        fclose(file);
        free(map);
        return NULL;
    }
    map->grid = allocate_map(map->width, map->height);
    if (!map->grid) {
        fclose(file);
        free(map);
        return NULL;
    }
    load_map_content(file, map);
    fclose(file);
    if (validate_map(map) == -1) {
        free_map(map);
        return NULL;
    }
    update_box_storage_count(map);
    return map;
}

void free_map(map_t *map)
{
    int i;

    if (!map)
        return;
    if (map->grid) {
        for (i = 0; i < map->height; i++)
            free(map->grid[i]);
        free(map->grid);
    }
    free(map);
}
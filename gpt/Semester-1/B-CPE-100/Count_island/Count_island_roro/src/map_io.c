/*
** EPITECH PROJECT, 2025
** Count_island_roro
** File description:
** Map loading, validation and printing
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "count_island.h"

static char *strip_newline(char *s)
{
    size_t len;

    if (s == NULL)
        return NULL;
    len = strlen(s);
    if (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'))
        s[len - 1] = '\0';
    return s;
}

static int parse_rows(const char *s, int *out)
{
    long v;
    char *end;

    if (s == NULL || out == NULL)
        return -1;
    v = strtol(s, &end, 10);
    if (end == s || *end != '\0' || v <= 0 || v > 10000)
        return -1;
    *out = (int)v;
    return 0;
}

static int read_rows_line(FILE *fp, int *rows)
{
    char *line;
    size_t cap;
    int status;

    line = NULL;
    cap = 0;
    if (getline(&line, &cap, fp) == -1) {
        free(line);
        return -1;
    }
    strip_newline(line);
    status = parse_rows(line, rows);
    free(line);
    if (status != 0)
        return -1;
    return 0;
}

static int read_grid(FILE *fp, map_t *map)
{
    char *line;
    size_t cap;
    int i;

    map->grid = calloc((size_t)map->rows, sizeof(char *));
    if (map->grid == NULL)
        return -1;
    map->cols = -1;
    line = NULL;
    cap = 0;
    for (i = 0; i < map->rows; ++i) {
        if (getline(&line, &cap, fp) == -1) {
            free(line);
            free_map(map);
            return -1;
        }
        strip_newline(line);
        if (map->cols == -1)
            map->cols = (int)strlen(line);
        map->grid[i] = strdup(line);
        if (map->grid[i] == NULL) {
            free(line);
            free_map(map);
            return -1;
        }
    }
    free(line);
    return 0;
}

int load_map(const char *path, map_t *map)
{
    FILE *fp;
    int status;

    if (path == NULL || map == NULL)
        return -1;
    fp = fopen(path, "r");
    if (fp == NULL)
        return -1;
    status = read_rows_line(fp, &map->rows);
    if (status == 0)
        status = read_grid(fp, map);
    fclose(fp);
    return status;
}

int validate_map(map_t *map)
{
    int r;
    int c;

    if (map == NULL || map->grid == NULL)
        return -1;
    if (map->rows <= 0 || map->cols <= 0)
        return -1;
    for (r = 0; r < map->rows; ++r) {
        if ((int)strlen(map->grid[r]) != map->cols)
            return -1;
        for (c = 0; c < map->cols; ++c) {
            if (map->grid[r][c] != 'X' && map->grid[r][c] != '.')
                return -1;
        }
    }
    return 0;
}

void print_map(const map_t *map)
{
    int r;

    if (map == NULL)
        return;
    for (r = 0; r < map->rows; ++r)
        printf("%s\n", map->grid[r]);
}

void free_map(map_t *map)
{
    int r;

    if (map == NULL || map->grid == NULL)
        return;
    for (r = 0; r < map->rows; ++r)
        free(map->grid[r]);
    free(map->grid);
    map->grid = NULL;
}

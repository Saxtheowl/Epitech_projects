/*
** EPITECH PROJECT, 2025
** BSQ_roro
** File description:
** Map IO
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bsq.h"

static char *strip_newline(char *s)
{
    size_t n;

    if (!s)
        return NULL;
    n = strlen(s);
    if (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r'))
        s[n - 1] = '\0';
    return s;
}

static int parse_rows(const char *s, int *out)
{
    long v;
    char *end;

    v = strtol(s, &end, 10);
    if (end == s || *end != '\0' || v <= 0 || v > 100000)
        return -1;
    *out = (int)v;
    return 0;
}

int load_map(const char *path, map_t *map)
{
    FILE *fp;
    char *line;
    size_t cap;
    int i;

    fp = fopen(path, "r");
    if (!fp)
        return -1;
    line = NULL;
    cap = 0;
    if (getline(&line, &cap, fp) == -1) {
        free(line);
        fclose(fp);
        return -1;
    }
    strip_newline(line);
    if (parse_rows(line, &map->rows) != 0) {
        free(line);
        fclose(fp);
        return -1;
    }
    free(line);
    map->grid = calloc((size_t)map->rows, sizeof(char *));
    if (!map->grid) {
        fclose(fp);
        return -1;
    }
    map->cols = -1;
    line = NULL;
    cap = 0;
    for (i = 0; i < map->rows; ++i) {
        if (getline(&line, &cap, fp) == -1) {
            free(line);
            fclose(fp);
            free_map(map);
            return -1;
        }
        strip_newline(line);
        if (map->cols == -1)
            map->cols = (int)strlen(line);
        map->grid[i] = strdup(line);
        if (!map->grid[i]) {
            free(line);
            fclose(fp);
            free_map(map);
            return -1;
        }
    }
    free(line);
    fclose(fp);
    return 0;
}

int validate_map(map_t *map)
{
    int r;
    int c;

    if (!map || !map->grid)
        return -1;
    if (map->rows <= 0 || map->cols <= 0)
        return -1;
    for (r = 0; r < map->rows; ++r) {
        if ((int)strlen(map->grid[r]) != map->cols)
            return -1;
        for (c = 0; c < map->cols; ++c) {
            if (map->grid[r][c] != '.' && map->grid[r][c] != 'o')
                return -1;
        }
    }
    return 0;
}

void print_map(const map_t *map)
{
    int r;

    for (r = 0; r < map->rows; ++r)
        printf("%s\n", map->grid[r]);
}

void free_map(map_t *map)
{
    int r;

    if (!map || !map->grid)
        return;
    for (r = 0; r < map->rows; ++r)
        free(map->grid[r]);
    free(map->grid);
    map->grid = NULL;
}

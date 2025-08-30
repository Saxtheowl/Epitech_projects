/*
** EPITECH PROJECT, 2024
** map_parser.c
** File description:
** Map parsing functions for BSQ
*/

#include <stdlib.h>
#include "../include/bsq.h"

int is_valid_char(char c)
{
    return (c == '.' || c == 'o');
}

static int count_lines(char const *content)
{
    int lines = 0;
    int i = 0;

    while (content[i]) {
        if (content[i] == '\n')
            lines++;
        i++;
    }
    return lines;
}

static int get_line_length(char const *content, int start)
{
    int len = 0;

    while (content[start + len] && content[start + len] != '\n')
        len++;
    return len;
}

int parse_map(char const *content, map_t *map)
{
    int i = 0;
    int line = 0;
    int col = 0;
    int line_start = 0;

    if (content == NULL || map == NULL)
        return -1;
    
    while (content[i] && content[i] != '\n')
        i++;
    
    if (content[i] != '\n')
        return -1;
    
    map->rows = my_atoi(content);
    if (map->rows <= 0)
        return -1;
    
    i++;
    line_start = i;
    map->cols = get_line_length(content, line_start);
    
    if (map->cols <= 0)
        return -1;
    
    map->grid = malloc(sizeof(char *) * map->rows);
    if (map->grid == NULL)
        return -1;
    
    line = 0;
    while (line < map->rows) {
        map->grid[line] = malloc(map->cols + 1);
        if (map->grid[line] == NULL)
            return -1;
        col = 0;
        while (col < map->cols && content[i] && content[i] != '\n') {
            if (!is_valid_char(content[i]))
                return -1;
            map->grid[line][col] = content[i];
            col++;
            i++;
        }
        if (col != map->cols)
            return -1;
        map->grid[line][col] = '\0';
        if (content[i] == '\n')
            i++;
        line++;
    }
    
    return 0;
}
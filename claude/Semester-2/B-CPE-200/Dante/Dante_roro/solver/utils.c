/*
** EPITECH PROJECT, 2024
** Dante's Star
** File description:
** Utility functions for maze operations
*/

#define _GNU_SOURCE
#include "../include/dante.h"

maze_t *create_maze(int width, int height)
{
    maze_t *maze = malloc(sizeof(maze_t));
    int i, j;

    if (!maze)
        return NULL;

    maze->width = width;
    maze->height = height;
    maze->grid = malloc(height * sizeof(char *));

    if (!maze->grid) {
        free(maze);
        return NULL;
    }

    for (i = 0; i < height; i++) {
        maze->grid[i] = malloc(width + 1);
        if (!maze->grid[i]) {
            for (j = 0; j < i; j++)
                free(maze->grid[j]);
            free(maze->grid);
            free(maze);
            return NULL;
        }
        for (j = 0; j < width; j++) {
            maze->grid[i][j] = WALL;
        }
        maze->grid[i][width] = '\0';
    }

    return maze;
}

void free_maze(maze_t *maze)
{
    int i;

    if (!maze)
        return;

    if (maze->grid) {
        for (i = 0; i < maze->height; i++) {
            free(maze->grid[i]);
        }
        free(maze->grid);
    }
    free(maze);
}

void print_maze(maze_t *maze)
{
    int i;

    for (i = 0; i < maze->height; i++) {
        printf("%s", maze->grid[i]);
        if (i < maze->height - 1)
            printf("\n");
    }
}
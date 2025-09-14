#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

typedef struct {
    char **grid;
    int width;
    int height;
    int perfect;
} maze_t;

typedef struct {
    int x;
    int y;
} point_t;

// Maze generation
maze_t *create_maze(int width, int height, int perfect);
void generate_perfect_maze(maze_t *maze);
void generate_imperfect_maze(maze_t *maze);

// Recursive backtracking algorithm
void carve_path(maze_t *maze, int x, int y, char **visited);
void shuffle_directions(int directions[][2], int count);

// Utility functions
void print_maze(maze_t *maze);
void free_maze(maze_t *maze);
int is_valid_cell(maze_t *maze, int x, int y);

#endif
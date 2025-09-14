#ifndef SOLVER_H
#define SOLVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    char **grid;
    int width;
    int height;
} maze_t;

typedef struct {
    int x;
    int y;
} point_t;

// Maze loading and parsing
maze_t *load_maze(const char *filename);
void free_maze(maze_t *maze);

// Maze solving
int solve_maze(maze_t *maze);
int dfs(maze_t *maze, int x, int y, char **visited);

// Utility functions
void print_maze(maze_t *maze);
int is_valid_move(maze_t *maze, int x, int y, char **visited);

#endif
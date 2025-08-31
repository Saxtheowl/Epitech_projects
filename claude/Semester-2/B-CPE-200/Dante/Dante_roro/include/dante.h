/*
** EPITECH PROJECT, 2024
** Dante's Star
** File description:
** Header file for maze generation and solving
*/

#ifndef DANTE_H_
#define DANTE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define WALL 'X'
#define PATH '*'
#define SOLUTION 'o'

typedef struct point_s {
    int x;
    int y;
} point_t;

typedef struct maze_s {
    char **grid;
    int width;
    int height;
} maze_t;

typedef struct queue_node_s {
    point_t point;
    struct queue_node_s *next;
} queue_node_t;

typedef struct queue_s {
    queue_node_t *front;
    queue_node_t *rear;
} queue_t;

/* Generator functions */
maze_t *create_maze(int width, int height);
void free_maze(maze_t *maze);
void generate_perfect_maze(maze_t *maze);
void generate_imperfect_maze(maze_t *maze);
void print_maze(maze_t *maze);

/* Solver functions */
maze_t *load_maze(const char *filename);
int solve_maze(maze_t *maze);
int bfs_solve(maze_t *maze);
void print_solution(maze_t *maze);

/* Utility functions */
int is_valid_pos(maze_t *maze, int x, int y);
int is_wall(maze_t *maze, int x, int y);
void set_cell(maze_t *maze, int x, int y, char value);
char get_cell(maze_t *maze, int x, int y);

/* Queue functions */
queue_t *create_queue(void);
void enqueue(queue_t *queue, point_t point);
point_t dequeue(queue_t *queue);
int is_queue_empty(queue_t *queue);
void free_queue(queue_t *queue);

/* Random generation helpers */
void shuffle_directions(int *directions, int count);
int has_unvisited_neighbors(maze_t *maze, int x, int y, char **visited);
void recursive_backtrack(maze_t *maze, int x, int y, char **visited);

#endif /* !DANTE_H_ */
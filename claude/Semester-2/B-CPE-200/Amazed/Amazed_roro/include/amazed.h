/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Header file for amazed maze solver
*/

#ifndef AMAZED_H_
#define AMAZED_H_

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ROOMS 10000
#define MAX_TUNNELS 50000
#define MAX_ROBOTS 1000
#define MAX_LINE_LENGTH 1024

typedef struct room_s {
    char *name;
    int x;
    int y;
    int id;
    int is_start;
    int is_end;
    int *connections;
    int connection_count;
    int robot_id;
} room_t;

typedef struct tunnel_s {
    char *room1;
    char *room2;
    int room1_id;
    int room2_id;
} tunnel_t;

typedef struct maze_s {
    int robot_count;
    room_t *rooms;
    int room_count;
    tunnel_t *tunnels;
    int tunnel_count;
    int start_room;
    int end_room;
    int **adjacency_matrix;
} maze_t;

typedef struct path_s {
    int *rooms;
    int length;
    int robot_id;
} path_t;

typedef struct robot_s {
    int id;
    int current_room;
    int target_room;
    path_t *path;
    int path_index;
    int finished;
} robot_t;

typedef struct solution_s {
    robot_t *robots;
    int robot_count;
    int total_turns;
    char **moves;
    int move_count;
} solution_t;

/* Maze parsing */
maze_t *create_maze(void);
void cleanup_maze(maze_t *maze);
int parse_input(maze_t *maze);
int parse_number_of_robots(maze_t *maze, char *line);
int parse_room(maze_t *maze, char *line, int *is_start, int *is_end);
int parse_tunnel(maze_t *maze, char *line);

/* Room management */
int add_room(maze_t *maze, const char *name, int x, int y, int is_start, int is_end);
int find_room_by_name(maze_t *maze, const char *name);
void add_connection(maze_t *maze, int room1_id, int room2_id);

/* Graph algorithms */
int *find_shortest_path(maze_t *maze, int start, int end, int *path_length);
int **find_all_paths(maze_t *maze, int *path_count);
void create_adjacency_matrix(maze_t *maze);

/* Solution generation */
solution_t *solve_maze(maze_t *maze);
void cleanup_solution(solution_t *solution);
int simulate_robots(maze_t *maze, solution_t *solution);

/* Output */
void print_maze_description(maze_t *maze);
void print_solution(maze_t *maze, solution_t *solution);

/* Utility functions */
char *my_strdup(const char *s);
int my_strcmp(const char *s1, const char *s2);
int my_strlen(const char *s);
void print_error(const char *message);

#endif /* !AMAZED_H_ */
/*
** EPITECH PROJECT, 2024
** Game of Stones
** File description:
** Main header file
*/

#ifndef GAME_OF_STONES_H_
#define GAME_OF_STONES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define ERROR_EXIT 84
#define SUCCESS_EXIT 0
#define MAX_NAME_LEN 256
#define MAX_LINE_LEN 1024
#define INF 999999

typedef struct person_s {
    char name[MAX_NAME_LEN];
    int id;
    struct person_s *next;
} person_t;

typedef struct graph_s {
    int **friendship_matrix;
    int **conspiracy_matrix;
    int **distance_matrix;
    person_t *persons;
    int person_count;
    int capacity;
} graph_t;

// Function prototypes

// Main functions
int links_mode(char *friendship_file, char *person1, char *person2);
int plots_mode(char *friendship_file, char *conspiracy_file, int max_distance);

// Parser functions
graph_t *init_graph(void);
void free_graph(graph_t *graph);
int parse_friendship_file(graph_t *graph, char *filename);
int parse_conspiracy_file(graph_t *graph, char *filename);
int get_person_id(graph_t *graph, char *name);
int add_person(graph_t *graph, char *name);

// Graph algorithms
void floyd_warshall(graph_t *graph);
int bfs_distance(graph_t *graph, int start, int end);
void print_distance_matrix(graph_t *graph, int max_distance);

// Plots analysis
int analyze_plots(graph_t *graph, int max_distance);
int find_direct_enemies(graph_t *graph, int **enemies);
int find_conspiracy_chain(graph_t *graph, int *enemies, int enemy_count, 
                         int max_distance);

// Utility functions
char *trim_whitespace(char *str);
int compare_persons(const void *a, const void *b);
void sort_persons(graph_t *graph);

#endif /* !GAME_OF_STONES_H_ */
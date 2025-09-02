/*
** EPITECH PROJECT, 2025
** Game of Stones
** File description:
** Main header file for Game of Stones - Graph theory and conspiracies
*/

#ifndef GAME_OF_STONES_H_
#define GAME_OF_STONES_H_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_NAME_LEN 256
#define MAX_LINE_LEN 512
#define MAX_PEOPLE 1000
#define INF 9999

typedef struct person_s {
    char name[MAX_NAME_LEN];
    int index;
} person_t;

typedef struct graph_s {
    int **adjacency_matrix;
    int **distance_matrix;
    char **names;
    int size;
    int capacity;
} graph_t;

typedef struct conspiracy_s {
    int plotter;
    int target;
} conspiracy_t;

typedef struct conspiracies_s {
    conspiracy_t *list;
    int count;
    int capacity;
} conspiracies_t;

// Core functions
int game_of_stones_main(int argc, char **argv);
void display_help(void);

// Graph operations
graph_t *create_graph(void);
void free_graph(graph_t *graph);
int add_person(graph_t *graph, const char *name);
int find_person(graph_t *graph, const char *name);
void add_friendship(graph_t *graph, int person1, int person2);
void calculate_shortest_paths(graph_t *graph);

// File parsing
graph_t *parse_friendship_file(const char *filename);
conspiracies_t *parse_conspiracy_file(const char *filename, graph_t *graph);

// Links mode
int links_mode(const char *filename, const char *person1, const char *person2);

// Plots mode
int plots_mode(const char *fr_file, const char *cr_file, int max_distance);

// Conspiracy resolution
int resolve_conspiracies(graph_t *graph, conspiracies_t *conspiracies, int max_distance);
void print_conspiracy_chains(graph_t *graph, conspiracies_t *conspiracies);

// Utility functions
void print_matrix(graph_t *graph, int max_distance);
void print_names_list(graph_t *graph);

#endif /* !GAME_OF_STONES_H_ */
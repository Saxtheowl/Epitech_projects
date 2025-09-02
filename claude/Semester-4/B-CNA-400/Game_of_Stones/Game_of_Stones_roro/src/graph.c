/*
** EPITECH PROJECT, 2025
** Game of Stones
** File description:
** Graph operations and algorithms
*/

#include "game_of_stones.h"

graph_t *create_graph(void)
{
    graph_t *graph = malloc(sizeof(graph_t));
    if (!graph)
        return NULL;
    
    graph->capacity = 100;
    graph->size = 0;
    
    graph->adjacency_matrix = malloc(sizeof(int*) * graph->capacity);
    graph->distance_matrix = malloc(sizeof(int*) * graph->capacity);
    graph->names = malloc(sizeof(char*) * graph->capacity);
    
    if (!graph->adjacency_matrix || !graph->distance_matrix || !graph->names) {
        free_graph(graph);
        return NULL;
    }
    
    for (int i = 0; i < graph->capacity; i++) {
        graph->adjacency_matrix[i] = calloc(graph->capacity, sizeof(int));
        graph->distance_matrix[i] = calloc(graph->capacity, sizeof(int));
        graph->names[i] = NULL;
        
        if (!graph->adjacency_matrix[i] || !graph->distance_matrix[i]) {
            free_graph(graph);
            return NULL;
        }
    }
    
    return graph;
}

void free_graph(graph_t *graph)
{
    if (!graph)
        return;
        
    if (graph->adjacency_matrix) {
        for (int i = 0; i < graph->capacity; i++) {
            free(graph->adjacency_matrix[i]);
        }
        free(graph->adjacency_matrix);
    }
    
    if (graph->distance_matrix) {
        for (int i = 0; i < graph->capacity; i++) {
            free(graph->distance_matrix[i]);
        }
        free(graph->distance_matrix);
    }
    
    if (graph->names) {
        for (int i = 0; i < graph->size; i++) {
            free(graph->names[i]);
        }
        free(graph->names);
    }
    
    free(graph);
}

int add_person(graph_t *graph, const char *name)
{
    if (!graph || !name)
        return -1;
    
    // Check if person already exists
    int existing = find_person(graph, name);
    if (existing >= 0)
        return existing;
    
    if (graph->size >= graph->capacity)
        return -1;
    
    graph->names[graph->size] = strdup(name);
    if (!graph->names[graph->size])
        return -1;
    
    return graph->size++;
}

int find_person(graph_t *graph, const char *name)
{
    if (!graph || !name)
        return -1;
        
    for (int i = 0; i < graph->size; i++) {
        if (graph->names[i] && strcmp(graph->names[i], name) == 0) {
            return i;
        }
    }
    
    return -1;
}

void add_friendship(graph_t *graph, int person1, int person2)
{
    if (!graph || person1 < 0 || person2 < 0 || 
        person1 >= graph->size || person2 >= graph->size)
        return;
    
    graph->adjacency_matrix[person1][person2] = 1;
    graph->adjacency_matrix[person2][person1] = 1;
}

void calculate_shortest_paths(graph_t *graph)
{
    if (!graph)
        return;
    
    // Initialize distance matrix
    for (int i = 0; i < graph->capacity; i++) {
        for (int j = 0; j < graph->capacity; j++) {
            if (i == j) {
                graph->distance_matrix[i][j] = 0;
            } else if (i < graph->size && j < graph->size && graph->adjacency_matrix[i][j] == 1) {
                graph->distance_matrix[i][j] = 1;
            } else {
                graph->distance_matrix[i][j] = INF;
            }
        }
    }
    
    // Floyd-Warshall algorithm
    for (int k = 0; k < graph->size; k++) {
        for (int i = 0; i < graph->size; i++) {
            for (int j = 0; j < graph->size; j++) {
                if (graph->distance_matrix[i][k] != INF && 
                    graph->distance_matrix[k][j] != INF &&
                    graph->distance_matrix[i][k] + graph->distance_matrix[k][j] < graph->distance_matrix[i][j]) {
                    graph->distance_matrix[i][j] = graph->distance_matrix[i][k] + graph->distance_matrix[k][j];
                }
            }
        }
    }
}
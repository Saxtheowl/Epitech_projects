/*
** EPITECH PROJECT, 2024
** Game of Stones
** File description:
** Graph data structure and operations
*/

#include "game_of_stones.h"

graph_t *init_graph(void)
{
    graph_t *graph = malloc(sizeof(graph_t));
    
    if (!graph)
        return NULL;
    
    graph->friendship_matrix = NULL;
    graph->conspiracy_matrix = NULL;
    graph->distance_matrix = NULL;
    graph->persons = NULL;
    graph->person_count = 0;
    graph->capacity = 0;
    
    return graph;
}

static void free_matrix(int **matrix, int size)
{
    if (!matrix)
        return;
    
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void free_graph(graph_t *graph)
{
    if (!graph)
        return;
    
    free_matrix(graph->friendship_matrix, graph->person_count);
    free_matrix(graph->conspiracy_matrix, graph->person_count);
    free_matrix(graph->distance_matrix, graph->person_count);
    
    person_t *current = graph->persons;
    while (current) {
        person_t *next = current->next;
        free(current);
        current = next;
    }
    
    free(graph);
}

static int **allocate_matrix(int size)
{
    int **matrix = malloc(sizeof(int *) * size);
    
    if (!matrix)
        return NULL;
    
    for (int i = 0; i < size; i++) {
        matrix[i] = malloc(sizeof(int) * size);
        if (!matrix[i]) {
            free_matrix(matrix, i);
            return NULL;
        }
        
        for (int j = 0; j < size; j++) {
            matrix[i][j] = (i == j) ? 0 : INF;
        }
    }
    
    return matrix;
}

static int resize_matrices(graph_t *graph, int new_size)
{
    // Allocate new matrices
    int **new_friendship = allocate_matrix(new_size);
    int **new_conspiracy = allocate_matrix(new_size);
    int **new_distance = allocate_matrix(new_size);
    
    if (!new_friendship || !new_conspiracy || !new_distance) {
        free_matrix(new_friendship, new_size);
        free_matrix(new_conspiracy, new_size);
        free_matrix(new_distance, new_size);
        return -1;
    }
    
    // Copy old data
    if (graph->friendship_matrix) {
        for (int i = 0; i < graph->person_count; i++) {
            for (int j = 0; j < graph->person_count; j++) {
                new_friendship[i][j] = graph->friendship_matrix[i][j];
                new_conspiracy[i][j] = graph->conspiracy_matrix[i][j];
                new_distance[i][j] = graph->distance_matrix[i][j];
            }
        }
    }
    
    // Free old matrices
    free_matrix(graph->friendship_matrix, graph->person_count);
    free_matrix(graph->conspiracy_matrix, graph->person_count);
    free_matrix(graph->distance_matrix, graph->person_count);
    
    // Set new matrices
    graph->friendship_matrix = new_friendship;
    graph->conspiracy_matrix = new_conspiracy;
    graph->distance_matrix = new_distance;
    graph->capacity = new_size;
    
    return 0;
}

int get_person_id(graph_t *graph, char *name)
{
    person_t *current = graph->persons;
    
    while (current) {
        if (strcmp(current->name, name) == 0)
            return current->id;
        current = current->next;
    }
    
    return -1;
}

int add_person(graph_t *graph, char *name)
{
    // Check if person already exists
    int existing_id = get_person_id(graph, name);
    if (existing_id != -1)
        return existing_id;
    
    // Resize matrices if needed
    if (graph->person_count >= graph->capacity) {
        int new_capacity = graph->capacity == 0 ? 10 : graph->capacity * 2;
        if (resize_matrices(graph, new_capacity) == -1)
            return -1;
    }
    
    // Add new person
    person_t *new_person = malloc(sizeof(person_t));
    if (!new_person)
        return -1;
    
    strncpy(new_person->name, name, MAX_NAME_LEN - 1);
    new_person->name[MAX_NAME_LEN - 1] = '\0';
    new_person->id = graph->person_count;
    new_person->next = graph->persons;
    graph->persons = new_person;
    
    return graph->person_count++;
}

void floyd_warshall(graph_t *graph)
{
    if (!graph || !graph->friendship_matrix || !graph->distance_matrix)
        return;
    
    // Initialize distance matrix with friendship matrix
    for (int i = 0; i < graph->person_count; i++) {
        for (int j = 0; j < graph->person_count; j++) {
            if (i == j) {
                graph->distance_matrix[i][j] = 0;
            } else if (graph->friendship_matrix[i][j] == 1) {
                graph->distance_matrix[i][j] = 1;
            } else {
                graph->distance_matrix[i][j] = INF;
            }
        }
    }
    
    // Floyd-Warshall algorithm
    for (int k = 0; k < graph->person_count; k++) {
        for (int i = 0; i < graph->person_count; i++) {
            for (int j = 0; j < graph->person_count; j++) {
                if (graph->distance_matrix[i][k] != INF &&
                    graph->distance_matrix[k][j] != INF &&
                    graph->distance_matrix[i][k] + graph->distance_matrix[k][j] <
                    graph->distance_matrix[i][j]) {
                    graph->distance_matrix[i][j] =
                        graph->distance_matrix[i][k] + graph->distance_matrix[k][j];
                }
            }
        }
    }
}
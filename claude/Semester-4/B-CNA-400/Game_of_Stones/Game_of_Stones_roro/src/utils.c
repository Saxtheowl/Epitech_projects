/*
** EPITECH PROJECT, 2025
** Game of Stones
** File description:
** Utility functions for debugging and display
*/

#include "game_of_stones.h"

void print_matrix(graph_t *graph, int max_distance)
{
    if (!graph)
        return;
    
    printf("Distance Matrix (max distance: %d):\n", max_distance);
    printf("     ");
    
    for (int i = 0; i < graph->size; i++) {
        printf("%8s", graph->names[i]);
    }
    printf("\n");
    
    for (int i = 0; i < graph->size; i++) {
        printf("%8s", graph->names[i]);
        for (int j = 0; j < graph->size; j++) {
            if (graph->distance_matrix[i][j] == INF) {
                printf("%8s", "INF");
            } else {
                printf("%8d", graph->distance_matrix[i][j]);
            }
        }
        printf("\n");
    }
}

void print_names_list(graph_t *graph)
{
    if (!graph)
        return;
    
    printf("People in the network (%d total):\n", graph->size);
    for (int i = 0; i < graph->size; i++) {
        printf("%d: %s\n", i, graph->names[i]);
    }
}
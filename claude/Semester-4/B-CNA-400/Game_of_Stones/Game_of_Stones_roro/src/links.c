/*
** EPITECH PROJECT, 2025
** Game of Stones
** File description:
** Links mode implementation
*/

#include "game_of_stones.h"

int links_mode(const char *filename, const char *person1, const char *person2)
{
    if (!filename || !person1 || !person2) {
        fprintf(stderr, "Error: Invalid parameters\n");
        return 84;
    }
    
    graph_t *graph = parse_friendship_file(filename);
    if (!graph) {
        return 84;
    }
    
    int idx1 = find_person(graph, person1);
    int idx2 = find_person(graph, person2);
    
    if (idx1 < 0) {
        fprintf(stderr, "Error: Person '%s' not found\n", person1);
        free_graph(graph);
        return 84;
    }
    
    if (idx2 < 0) {
        fprintf(stderr, "Error: Person '%s' not found\n", person2);
        free_graph(graph);
        return 84;
    }
    
    int distance = graph->distance_matrix[idx1][idx2];
    
    if (distance == INF) {
        printf("Degree of separation between %s and %s: -1\n", person1, person2);
    } else {
        printf("Degree of separation between %s and %s: %d\n", person1, person2, distance);
    }
    
    free_graph(graph);
    return 0;
}
/*
** EPITECH PROJECT, 2025
** Game of Stones
** File description:
** Plots mode implementation
*/

#include "game_of_stones.h"

static int compare_names(const void *a, const void *b) {
    const char **name_a = (const char **)a;
    const char **name_b = (const char **)b;
    return strcmp(*name_a, *name_b);
}

static void print_sorted_names(graph_t *graph)
{
    char **sorted_names = malloc(sizeof(char*) * graph->size);
    if (!sorted_names) return;
    
    for (int i = 0; i < graph->size; i++) {
        sorted_names[i] = graph->names[i];
    }
    
    qsort(sorted_names, graph->size, sizeof(char*), compare_names);
    
    printf("Names:\n");
    for (int i = 0; i < graph->size; i++) {
        printf("%s\n", sorted_names[i]);
    }
    
    free(sorted_names);
}


static void print_distance_matrix(graph_t *graph, int max_distance)
{
    char **sorted_names = malloc(sizeof(char*) * graph->size);
    int *sorted_indices = malloc(sizeof(int) * graph->size);
    
    if (!sorted_names || !sorted_indices) return;
    
    for (int i = 0; i < graph->size; i++) {
        sorted_names[i] = graph->names[i];
        sorted_indices[i] = i;
    }
    
    // Sort by name and keep track of original indices
    for (int i = 0; i < graph->size - 1; i++) {
        for (int j = i + 1; j < graph->size; j++) {
            if (strcmp(sorted_names[i], sorted_names[j]) > 0) {
                char *temp_name = sorted_names[i];
                sorted_names[i] = sorted_names[j];
                sorted_names[j] = temp_name;
                
                int temp_idx = sorted_indices[i];
                sorted_indices[i] = sorted_indices[j];
                sorted_indices[j] = temp_idx;
            }
        }
    }
    
    printf("Relationships:\n");
    for (int i = 0; i < graph->size; i++) {
        for (int j = 0; j < graph->size; j++) {
            int dist = graph->distance_matrix[sorted_indices[i]][sorted_indices[j]];
            if (dist == INF || dist > max_distance) {
                printf("0 ");
            } else {
                printf("%d ", dist);
            }
        }
        printf("\n");
    }
    
    free(sorted_names);
    free(sorted_indices);
}

int plots_mode(const char *fr_file, const char *cr_file, int max_distance)
{
    if (!fr_file || !cr_file || max_distance <= 0) {
        fprintf(stderr, "Error: Invalid parameters\n");
        return 84;
    }
    
    graph_t *graph = parse_friendship_file(fr_file);
    if (!graph) {
        return 84;
    }
    
    conspiracies_t *conspiracies = parse_conspiracy_file(cr_file, graph);
    if (!conspiracies) {
        free_graph(graph);
        return 84;
    }
    
    print_sorted_names(graph);
    print_distance_matrix(graph, max_distance);
    
    printf("Conspiracies:\n");
    int result = resolve_conspiracies(graph, conspiracies, max_distance);
    
    free(conspiracies->list);
    free(conspiracies);
    free_graph(graph);
    
    return result;
}
/*
** EPITECH PROJECT, 2025
** Game of Stones
** File description:
** Conspiracy resolution algorithms
*/

#include "game_of_stones.h"

static int find_cersei(graph_t *graph)
{
    for (int i = 0; i < graph->size; i++) {
        if (strstr(graph->names[i], "Cersei") != NULL) {
            return i;
        }
    }
    return -1;
}

static bool is_close_friend(graph_t *graph, int person, int cersei_idx, int max_distance)
{
    if (person == cersei_idx) return true;
    int distance = graph->distance_matrix[cersei_idx][person];
    return (distance != INF && distance <= max_distance);
}


static void print_chain_conspiracy(graph_t *graph, int *chain, int chain_length)
{
    for (int i = 0; i < chain_length; i++) {
        printf("%s", graph->names[chain[i]]);
        if (i < chain_length - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

static bool find_conspiracy_chain(graph_t *graph, conspiracies_t *conspiracies, 
                                  int target, int cersei_idx, int max_distance, 
                                  int *chain, int chain_length, bool *used)
{
    // Direct conspiracy from close friends
    for (int i = 0; i < conspiracies->count; i++) {
        int plotter = conspiracies->list[i].plotter;
        int victim = conspiracies->list[i].target;
        
        if (victim == target && !used[i] && 
            is_close_friend(graph, plotter, cersei_idx, max_distance)) {
            chain[chain_length] = plotter;
            chain[chain_length + 1] = target;
            print_chain_conspiracy(graph, chain, chain_length + 2);
            used[i] = true;
            return true;
        }
    }
    
    // Try indirect conspiracy chains
    for (int i = 0; i < conspiracies->count; i++) {
        int plotter = conspiracies->list[i].plotter;
        int victim = conspiracies->list[i].target;
        
        if (victim == target && !used[i]) {
            chain[chain_length] = plotter;
            chain[chain_length + 1] = target;
            used[i] = true;
            
            if (find_conspiracy_chain(graph, conspiracies, plotter, cersei_idx, 
                                     max_distance, chain, chain_length + 2, used)) {
                return true;
            }
            used[i] = false;
        }
    }
    
    return false;
}

int resolve_conspiracies(graph_t *graph, conspiracies_t *conspiracies, int max_distance)
{
    if (!graph || !conspiracies)
        return 84;
    
    int cersei_idx = find_cersei(graph);
    if (cersei_idx < 0) {
        printf("Result:\nThere is only one way out: treason!\n");
        return 0;
    }
    
    // Find direct enemies (those plotting against Cersei)
    bool *direct_enemies = calloc(graph->size, sizeof(bool));
    bool *conspiracy_used = calloc(conspiracies->count, sizeof(bool));
    int *chain = malloc(sizeof(int) * (graph->size * 2));
    
    if (!direct_enemies || !conspiracy_used || !chain) {
        free(direct_enemies);
        free(conspiracy_used);
        free(chain);
        return 84;
    }
    
    for (int i = 0; i < conspiracies->count; i++) {
        if (conspiracies->list[i].target == cersei_idx) {
            direct_enemies[conspiracies->list[i].plotter] = true;
        }
    }
    
    bool all_resolved = true;
    
    // Try to resolve each direct enemy
    for (int i = 0; i < graph->size; i++) {
        if (direct_enemies[i]) {
            if (!find_conspiracy_chain(graph, conspiracies, i, cersei_idx, 
                                      max_distance, chain, 0, conspiracy_used)) {
                printf("No conspiracy possible against %s\n", graph->names[i]);
                all_resolved = false;
            }
        }
    }
    
    printf("Result:\n");
    if (all_resolved) {
        printf("The stone is safe!\n");
    } else {
        printf("There is only one way out: treason!\n");
    }
    
    free(direct_enemies);
    free(conspiracy_used);
    free(chain);
    return 0;
}

void print_conspiracy_chains(graph_t *graph, conspiracies_t *conspiracies)
{
    if (!graph || !conspiracies)
        return;
    
    for (int i = 0; i < conspiracies->count; i++) {
        conspiracy_t *conspiracy = &conspiracies->list[i];
        printf("%s -> %s\n", 
               graph->names[conspiracy->plotter],
               graph->names[conspiracy->target]);
    }
}
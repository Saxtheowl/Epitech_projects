/*
** EPITECH PROJECT, 2024
** Game of Stones
** File description:
** Plots mode implementation
*/

#include "game_of_stones.h"

void print_distance_matrix(graph_t *graph, int max_distance)
{
    // Get sorted array of persons
    person_t **sorted_persons = malloc(graph->person_count * sizeof(person_t *));
    if (!sorted_persons)
        return;
    
    person_t *current = graph->persons;
    int count = 0;
    while (current && count < graph->person_count) {
        sorted_persons[count++] = current;
        current = current->next;
    }
    
    // Sort persons alphabetically
    for (int i = 0; i < graph->person_count - 1; i++) {
        for (int j = i + 1; j < graph->person_count; j++) {
            if (strcmp(sorted_persons[i]->name, sorted_persons[j]->name) > 0) {
                person_t *temp = sorted_persons[i];
                sorted_persons[i] = sorted_persons[j];
                sorted_persons[j] = temp;
            }
        }
    }
    
    // Print header
    printf("    ");
    for (int i = 0; i < graph->person_count; i++) {
        printf("%8s", sorted_persons[i]->name);
    }
    printf("\n");
    
    // Print matrix
    for (int i = 0; i < graph->person_count; i++) {
        printf("%8s", sorted_persons[i]->name);
        for (int j = 0; j < graph->person_count; j++) {
            int distance = graph->distance_matrix[sorted_persons[i]->id][sorted_persons[j]->id];
            if (distance > max_distance) {
                printf("%8s", "X");
            } else if (distance == INF) {
                printf("%8s", "X");
            } else {
                printf("%8d", distance);
            }
        }
        printf("\n");
    }
    
    free(sorted_persons);
}

int find_direct_enemies(graph_t *graph, int **enemies)
{
    int cersei_id = get_person_id(graph, "Cersei");
    int queen_id = get_person_id(graph, "Queen");
    
    if (cersei_id == -1 && queen_id == -1) {
        return 0; // No Crown to protect
    }
    
    *enemies = malloc(graph->person_count * sizeof(int));
    if (!*enemies)
        return -1;
    
    int enemy_count = 0;
    
    for (int i = 0; i < graph->person_count; i++) {
        bool is_enemy = false;
        
        if (cersei_id != -1 && graph->conspiracy_matrix[i][cersei_id] == 1) {
            is_enemy = true;
        }
        if (queen_id != -1 && graph->conspiracy_matrix[i][queen_id] == 1) {
            is_enemy = true;
        }
        
        if (is_enemy) {
            (*enemies)[enemy_count++] = i;
        }
    }
    
    return enemy_count;
}

static bool can_eliminate_enemy(graph_t *graph, int eliminator, int enemy, 
                               int max_distance)
{
    // Check if eliminator plots against enemy
    if (graph->conspiracy_matrix[eliminator][enemy] == 1)
        return true;
    
    // Check if eliminator can reach someone who plots against enemy
    for (int i = 0; i < graph->person_count; i++) {
        if (graph->conspiracy_matrix[i][enemy] == 1) {
            int distance = graph->distance_matrix[eliminator][i];
            if (distance != INF && distance <= max_distance) {
                return true;
            }
        }
    }
    
    return false;
}

static int find_best_eliminator(graph_t *graph, int *enemies, int enemy_count,
                               int *eliminated, int max_distance)
{
    int cersei_id = get_person_id(graph, "Cersei");
    int queen_id = get_person_id(graph, "Queen");
    
    int best_eliminator = -1;
    int min_distance_to_crown = INF;
    char best_name[MAX_NAME_LEN] = "";
    
    for (int person = 0; person < graph->person_count; person++) {
        // Skip if this person is a direct enemy
        bool is_direct_enemy = false;
        for (int i = 0; i < enemy_count; i++) {
            if (person == enemies[i]) {
                is_direct_enemy = true;
                break;
            }
        }
        if (is_direct_enemy)
            continue;
        
        // Check if this person can eliminate at least one remaining enemy
        bool can_eliminate_any = false;
        for (int i = 0; i < enemy_count; i++) {
            if (!eliminated[i] && can_eliminate_enemy(graph, person, enemies[i], max_distance)) {
                can_eliminate_any = true;
                break;
            }
        }
        
        if (!can_eliminate_any)
            continue;
        
        // Calculate distance to crown
        int distance_to_crown = INF;
        if (cersei_id != -1) {
            int d = graph->distance_matrix[person][cersei_id];
            if (d < distance_to_crown)
                distance_to_crown = d;
        }
        if (queen_id != -1) {
            int d = graph->distance_matrix[person][queen_id];
            if (d < distance_to_crown)
                distance_to_crown = d;
        }
        
        // Get person name
        person_t *current = graph->persons;
        while (current) {
            if (current->id == person) {
                // Check if this is better candidate
                if (distance_to_crown < min_distance_to_crown ||
                    (distance_to_crown == min_distance_to_crown && 
                     strcmp(current->name, best_name) < 0)) {
                    best_eliminator = person;
                    min_distance_to_crown = distance_to_crown;
                    strncpy(best_name, current->name, MAX_NAME_LEN - 1);
                    best_name[MAX_NAME_LEN - 1] = '\0';
                }
                break;
            }
            current = current->next;
        }
    }
    
    return best_eliminator;
}

int find_conspiracy_chain(graph_t *graph, int *enemies, int enemy_count, 
                         int max_distance)
{
    if (enemy_count == 0) {
        printf("The stone is safe!\n");
        return 0;
    }
    
    int *eliminated = calloc(enemy_count, sizeof(int));
    if (!eliminated)
        return -1;
    
    bool solution_found = true;
    
    // Try to find eliminators for each enemy
    while (true) {
        int best_eliminator = find_best_eliminator(graph, enemies, enemy_count, 
                                                  eliminated, max_distance);
        
        if (best_eliminator == -1) {
            solution_found = false;
            break;
        }
        
        // Mark enemies that this eliminator can handle
        bool eliminated_any = false;
        for (int i = 0; i < enemy_count; i++) {
            if (!eliminated[i] && can_eliminate_enemy(graph, best_eliminator, 
                                                     enemies[i], max_distance)) {
                eliminated[i] = 1;
                eliminated_any = true;
            }
        }
        
        if (!eliminated_any)
            break;
        
        // Get eliminator name
        person_t *current = graph->persons;
        while (current) {
            if (current->id == best_eliminator) {
                printf("%s\n", current->name);
                break;
            }
            current = current->next;
        }
        
        // Check if all enemies are eliminated
        bool all_eliminated = true;
        for (int i = 0; i < enemy_count; i++) {
            if (!eliminated[i]) {
                all_eliminated = false;
                break;
            }
        }
        
        if (all_eliminated) {
            printf("The stone is safe!\n");
            break;
        }
    }
    
    if (!solution_found) {
        printf("There is only one way out: treason!\n");
    }
    
    free(eliminated);
    return solution_found ? 0 : 1;
}

int analyze_plots(graph_t *graph, int max_distance)
{
    // Find direct enemies
    int *enemies = NULL;
    int enemy_count = find_direct_enemies(graph, &enemies);
    
    if (enemy_count == -1) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return -1;
    }
    
    if (enemy_count == 0) {
        printf("The stone is safe!\n");
        return 0;
    }
    
    // Find conspiracy chain
    int result = find_conspiracy_chain(graph, enemies, enemy_count, max_distance);
    
    free(enemies);
    return result;
}

int plots_mode(char *friendship_file, char *conspiracy_file, int max_distance)
{
    graph_t *graph = init_graph();
    if (!graph) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return ERROR_EXIT;
    }
    
    // Parse friendship file
    if (parse_friendship_file(graph, friendship_file) == -1) {
        free_graph(graph);
        return ERROR_EXIT;
    }
    
    // Parse conspiracy file
    if (parse_conspiracy_file(graph, conspiracy_file) == -1) {
        free_graph(graph);
        return ERROR_EXIT;
    }
    
    // Calculate shortest paths
    floyd_warshall(graph);
    
    // Print distance matrix
    print_distance_matrix(graph, max_distance);
    printf("\n");
    
    // Analyze plots
    if (analyze_plots(graph, max_distance) == -1) {
        free_graph(graph);
        return ERROR_EXIT;
    }
    
    free_graph(graph);
    return SUCCESS_EXIT;
}
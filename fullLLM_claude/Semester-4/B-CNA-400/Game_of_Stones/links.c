/*
** EPITECH PROJECT, 2024
** Game of Stones
** File description:
** Links mode implementation
*/

#include "game_of_stones.h"

static int bfs_queue_enqueue(int *queue, int *rear, int value)
{
    queue[++(*rear)] = value;
    return 0;
}

static int bfs_queue_dequeue(int *queue, int *front, int rear)
{
    if (*front > rear)
        return -1;
    return queue[(*front)++];
}

int bfs_distance(graph_t *graph, int start, int end)
{
    if (!graph || !graph->friendship_matrix || start == -1 || end == -1)
        return -1;
    
    if (start == end)
        return 0;
    
    int *visited = calloc(graph->person_count, sizeof(int));
    int *distance = calloc(graph->person_count, sizeof(int));
    int *queue = malloc(graph->person_count * sizeof(int));
    
    if (!visited || !distance || !queue) {
        free(visited);
        free(distance);
        free(queue);
        return -1;
    }
    
    int front = 0, rear = -1;
    
    // Initialize
    for (int i = 0; i < graph->person_count; i++) {
        distance[i] = -1;
    }
    
    visited[start] = 1;
    distance[start] = 0;
    bfs_queue_enqueue(queue, &rear, start);
    
    while (front <= rear) {
        int current = bfs_queue_dequeue(queue, &front, rear);
        if (current == -1)
            break;
        
        if (current == end) {
            int result = distance[end];
            free(visited);
            free(distance);
            free(queue);
            return result;
        }
        
        // Check all neighbors
        for (int i = 0; i < graph->person_count; i++) {
            if (graph->friendship_matrix[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                distance[i] = distance[current] + 1;
                bfs_queue_enqueue(queue, &rear, i);
            }
        }
    }
    
    free(visited);
    free(distance);
    free(queue);
    return -1; // Not connected
}

int links_mode(char *friendship_file, char *person1, char *person2)
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
    
    // Find person IDs
    int id1 = get_person_id(graph, person1);
    int id2 = get_person_id(graph, person2);
    
    if (id1 == -1) {
        printf("Person '%s' not found in friendship network\n", person1);
        free_graph(graph);
        return ERROR_EXIT;
    }
    
    if (id2 == -1) {
        printf("Person '%s' not found in friendship network\n", person2);
        free_graph(graph);
        return ERROR_EXIT;
    }
    
    // Calculate distance
    int distance = bfs_distance(graph, id1, id2);
    
    printf("%d\n", distance);
    
    free_graph(graph);
    return SUCCESS_EXIT;
}
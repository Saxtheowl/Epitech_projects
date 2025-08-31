/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Pathfinding algorithms implementation
*/

#include "../include/amazed.h"

void create_adjacency_matrix(maze_t *maze)
{
    int i, j;

    maze->adjacency_matrix = malloc(sizeof(int *) * maze->room_count);
    if (!maze->adjacency_matrix)
        return;
        
    for (i = 0; i < maze->room_count; i++) {
        maze->adjacency_matrix[i] = malloc(sizeof(int) * maze->room_count);
        if (!maze->adjacency_matrix[i])
            return;
        for (j = 0; j < maze->room_count; j++)
            maze->adjacency_matrix[i][j] = 0;
    }
    
    for (i = 0; i < maze->room_count; i++) {
        room_t *room = &maze->rooms[i];
        for (j = 0; j < room->connection_count; j++) {
            int connected_room = room->connections[j];
            maze->adjacency_matrix[i][connected_room] = 1;
        }
    }
}

int *find_shortest_path(maze_t *maze, int start, int end, int *path_length)
{
    int *distances = malloc(sizeof(int) * maze->room_count);
    int *previous = malloc(sizeof(int) * maze->room_count);
    int *visited = malloc(sizeof(int) * maze->room_count);
    int *path = NULL;
    int i, j, current, min_distance, path_index;

    if (!distances || !previous || !visited) {
        free(distances);
        free(previous);
        free(visited);
        return NULL;
    }
    
    for (i = 0; i < maze->room_count; i++) {
        distances[i] = __INT_MAX__;
        previous[i] = -1;
        visited[i] = 0;
    }
    
    distances[start] = 0;
    
    for (i = 0; i < maze->room_count; i++) {
        min_distance = __INT_MAX__;
        current = -1;
        
        for (j = 0; j < maze->room_count; j++) {
            if (!visited[j] && distances[j] < min_distance) {
                min_distance = distances[j];
                current = j;
            }
        }
        
        if (current == -1 || current == end)
            break;
            
        visited[current] = 1;
        
        for (j = 0; j < maze->room_count; j++) {
            if (!visited[j] && maze->adjacency_matrix[current][j] &&
                distances[current] + 1 < distances[j]) {
                distances[j] = distances[current] + 1;
                previous[j] = current;
            }
        }
    }
    
    if (distances[end] == __INT_MAX__) {
        free(distances);
        free(previous);
        free(visited);
        return NULL;
    }
    
    *path_length = distances[end] + 1;
    path = malloc(sizeof(int) * (*path_length));
    if (!path) {
        free(distances);
        free(previous);
        free(visited);
        return NULL;
    }
    
    path_index = *path_length - 1;
    current = end;
    while (current != -1) {
        path[path_index] = current;
        path_index--;
        current = previous[current];
    }
    
    free(distances);
    free(previous);
    free(visited);
    
    return path;
}
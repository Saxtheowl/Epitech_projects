/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Maze creation and management functions
*/

#include "../include/amazed.h"

maze_t *create_maze(void)
{
    maze_t *maze = malloc(sizeof(maze_t));
    
    if (!maze)
        return NULL;
        
    maze->robot_count = 0;
    maze->room_count = 0;
    maze->tunnel_count = 0;
    maze->start_room = -1;
    maze->end_room = -1;
    maze->adjacency_matrix = NULL;
    
    maze->rooms = malloc(sizeof(room_t) * MAX_ROOMS);
    maze->tunnels = malloc(sizeof(tunnel_t) * MAX_TUNNELS);
    
    if (!maze->rooms || !maze->tunnels) {
        free(maze->rooms);
        free(maze->tunnels);
        free(maze);
        return NULL;
    }
    
    return maze;
}

void cleanup_maze(maze_t *maze)
{
    int i;

    if (!maze)
        return;
        
    if (maze->rooms) {
        for (i = 0; i < maze->room_count; i++) {
            free(maze->rooms[i].name);
            free(maze->rooms[i].connections);
        }
        free(maze->rooms);
    }
    
    if (maze->tunnels) {
        for (i = 0; i < maze->tunnel_count; i++) {
            free(maze->tunnels[i].room1);
            free(maze->tunnels[i].room2);
        }
        free(maze->tunnels);
    }
    
    if (maze->adjacency_matrix) {
        for (i = 0; i < maze->room_count; i++)
            free(maze->adjacency_matrix[i]);
        free(maze->adjacency_matrix);
    }
    
    free(maze);
}

int add_room(maze_t *maze, const char *name, int x, int y, int is_start, int is_end)
{
    room_t *room;

    if (maze->room_count >= MAX_ROOMS)
        return -1;
        
    room = &maze->rooms[maze->room_count];
    room->name = my_strdup(name);
    if (!room->name)
        return -1;
        
    room->x = x;
    room->y = y;
    room->id = maze->room_count;
    room->is_start = is_start;
    room->is_end = is_end;
    room->robot_id = -1;
    room->connections = malloc(sizeof(int) * MAX_ROOMS);
    room->connection_count = 0;
    
    if (!room->connections) {
        free(room->name);
        return -1;
    }
    
    if (is_start)
        maze->start_room = maze->room_count;
    if (is_end)
        maze->end_room = maze->room_count;
        
    maze->room_count++;
    return room->id;
}

int find_room_by_name(maze_t *maze, const char *name)
{
    int i;

    for (i = 0; i < maze->room_count; i++) {
        if (my_strcmp(maze->rooms[i].name, name) == 0)
            return i;
    }
    return -1;
}

void add_connection(maze_t *maze, int room1_id, int room2_id)
{
    room_t *room1 = &maze->rooms[room1_id];
    room_t *room2 = &maze->rooms[room2_id];

    room1->connections[room1->connection_count] = room2_id;
    room1->connection_count++;
    
    room2->connections[room2->connection_count] = room1_id;
    room2->connection_count++;
}
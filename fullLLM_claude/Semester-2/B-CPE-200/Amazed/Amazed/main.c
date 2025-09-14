/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Multi-robot pathfinding in maze
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_ROOMS 1000
#define MAX_TUNNELS 10000
#define MAX_ROBOTS 1000

typedef struct room_s {
    char *name;
    int x, y;
    int id;
    int is_start;
    int is_end;
    struct room_s **connections;
    int connection_count;
} room_t;

typedef struct maze_s {
    room_t rooms[MAX_ROOMS];
    int room_count;
    int robot_count;
    int start_room;
    int end_room;
} maze_t;

typedef struct path_s {
    int *rooms;
    int length;
} path_t;

int my_strlen(char *str)
{
    int len = 0;
    
    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

char *my_strdup(char *str)
{
    char *dup;
    int i;
    
    if (!str)
        return NULL;
    dup = malloc(my_strlen(str) + 1);
    if (!dup)
        return NULL;
    for (i = 0; str[i]; i++)
        dup[i] = str[i];
    dup[i] = '\0';
    return dup;
}

int my_strcmp(char *s1, char *s2)
{
    int i = 0;
    
    if (!s1 || !s2)
        return -1;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}

int my_atoi(char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;
    
    if (!str)
        return 0;
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

char **split_line(char *line, char delimiter)
{
    char **tokens = malloc(sizeof(char*) * 10);
    int token_count = 0;
    int start = 0;
    int i;
    
    if (!tokens)
        return NULL;
    
    for (i = 0; line[i]; i++) {
        if (line[i] == delimiter || line[i] == '\n') {
            if (i > start) {
                tokens[token_count] = malloc(i - start + 1);
                if (!tokens[token_count])
                    return NULL;
                strncpy(tokens[token_count], line + start, i - start);
                tokens[token_count][i - start] = '\0';
                token_count++;
            }
            start = i + 1;
        }
    }
    
    if (i > start && line[start] != '\n') {
        tokens[token_count] = malloc(i - start + 1);
        if (!tokens[token_count])
            return NULL;
        strncpy(tokens[token_count], line + start, i - start);
        tokens[token_count][i - start] = '\0';
        token_count++;
    }
    
    tokens[token_count] = NULL;
    return tokens;
}

void free_tokens(char **tokens)
{
    int i;
    
    if (!tokens)
        return;
    for (i = 0; tokens[i]; i++)
        free(tokens[i]);
    free(tokens);
}

int find_room_by_name(maze_t *maze, char *name)
{
    int i;
    
    for (i = 0; i < maze->room_count; i++) {
        if (my_strcmp(maze->rooms[i].name, name) == 0)
            return i;
    }
    return -1;
}

int add_room(maze_t *maze, char *name, int x, int y)
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
    room->is_start = 0;
    room->is_end = 0;
    room->connections = malloc(sizeof(room_t*) * MAX_ROOMS);
    if (!room->connections)
        return -1;
    room->connection_count = 0;
    
    maze->room_count++;
    return room->id;
}

int add_tunnel(maze_t *maze, char *room1_name, char *room2_name)
{
    int room1_id = find_room_by_name(maze, room1_name);
    int room2_id = find_room_by_name(maze, room2_name);
    
    if (room1_id == -1 || room2_id == -1)
        return -1;
    
    maze->rooms[room1_id].connections[maze->rooms[room1_id].connection_count++] = &maze->rooms[room2_id];
    maze->rooms[room2_id].connections[maze->rooms[room2_id].connection_count++] = &maze->rooms[room1_id];
    
    return 0;
}

int parse_input(maze_t *maze)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_len;
    char **tokens;
    int is_start_next = 0;
    int is_end_next = 0;
    
    // Read robot count
    read_len = getline(&line, &len, stdin);
    if (read_len == -1)
        return -1;
    maze->robot_count = my_atoi(line);
    
    // Read rooms and tunnels
    while ((read_len = getline(&line, &len, stdin)) != -1) {
        if (read_len <= 1)
            break;
        
        // Remove newline
        if (line[read_len - 1] == '\n')
            line[read_len - 1] = '\0';
        
        // Skip comments
        if (line[0] == '#' && line[1] != '#')
            continue;
        
        // Handle commands
        if (my_strcmp(line, "##start") == 0) {
            is_start_next = 1;
            continue;
        }
        if (my_strcmp(line, "##end") == 0) {
            is_end_next = 1;
            continue;
        }
        
        // Check if it's a tunnel (contains '-')
        if (strchr(line, '-')) {
            tokens = split_line(line, '-');
            if (tokens && tokens[0] && tokens[1]) {
                add_tunnel(maze, tokens[0], tokens[1]);
            }
            free_tokens(tokens);
        } else {
            // It's a room
            tokens = split_line(line, ' ');
            if (tokens && tokens[0] && tokens[1] && tokens[2]) {
                int room_id = add_room(maze, tokens[0], my_atoi(tokens[1]), my_atoi(tokens[2]));
                if (room_id != -1) {
                    if (is_start_next) {
                        maze->rooms[room_id].is_start = 1;
                        maze->start_room = room_id;
                        is_start_next = 0;
                    }
                    if (is_end_next) {
                        maze->rooms[room_id].is_end = 1;
                        maze->end_room = room_id;
                        is_end_next = 0;
                    }
                }
            }
            free_tokens(tokens);
        }
    }
    
    if (line)
        free(line);
    return 0;
}

path_t find_shortest_path(maze_t *maze)
{
    int *distances = malloc(sizeof(int) * maze->room_count);
    int *previous = malloc(sizeof(int) * maze->room_count);
    int *visited = malloc(sizeof(int) * maze->room_count);
    path_t path;
    int current, i, j;
    int min_dist, min_id;
    
    path.rooms = NULL;
    path.length = 0;
    
    if (!distances || !previous || !visited)
        return path;
    
    // Initialize Dijkstra
    for (i = 0; i < maze->room_count; i++) {
        distances[i] = 999999;
        previous[i] = -1;
        visited[i] = 0;
    }
    distances[maze->start_room] = 0;
    
    // Dijkstra's algorithm
    for (i = 0; i < maze->room_count; i++) {
        min_dist = 999999;
        min_id = -1;
        
        for (j = 0; j < maze->room_count; j++) {
            if (!visited[j] && distances[j] < min_dist) {
                min_dist = distances[j];
                min_id = j;
            }
        }
        
        if (min_id == -1)
            break;
        
        current = min_id;
        visited[current] = 1;
        
        if (current == maze->end_room)
            break;
        
        for (j = 0; j < maze->rooms[current].connection_count; j++) {
            int neighbor = maze->rooms[current].connections[j]->id;
            int new_dist = distances[current] + 1;
            
            if (new_dist < distances[neighbor]) {
                distances[neighbor] = new_dist;
                previous[neighbor] = current;
            }
        }
    }
    
    // Reconstruct path
    if (distances[maze->end_room] != 999999) {
        path.length = distances[maze->end_room] + 1;
        path.rooms = malloc(sizeof(int) * path.length);
        if (path.rooms) {
            current = maze->end_room;
            for (i = path.length - 1; i >= 0; i--) {
                path.rooms[i] = current;
                current = previous[current];
            }
        }
    }
    
    free(distances);
    free(previous);
    free(visited);
    return path;
}

void print_output(maze_t *maze, path_t *path)
{
    int i, j, step;
    
    // Print number of robots
    printf("#number_of_robots\n%d\n", maze->robot_count);
    
    // Print rooms
    printf("#rooms\n");
    for (i = 0; i < maze->room_count; i++) {
        if (maze->rooms[i].is_start)
            printf("##start\n");
        if (maze->rooms[i].is_end)
            printf("##end\n");
        printf("%s %d %d\n", maze->rooms[i].name, maze->rooms[i].x, maze->rooms[i].y);
    }
    
    // Print tunnels
    printf("#tunnels\n");
    for (i = 0; i < maze->room_count; i++) {
        for (j = 0; j < maze->rooms[i].connection_count; j++) {
            if (maze->rooms[i].id < maze->rooms[i].connections[j]->id) {
                printf("%s-%s\n", maze->rooms[i].name, maze->rooms[i].connections[j]->name);
            }
        }
    }
    
    // Print moves
    printf("#moves\n");
    
    // Simple strategy: send robots one by one through the shortest path
    for (step = 1; step < path->length; step++) {
        int robots_moving = 0;
        
        for (i = 1; i <= maze->robot_count && i + step - 1 < path->length; i++) {
            if (robots_moving > 0)
                printf(" ");
            printf("P%d-%s", i, maze->rooms[path->rooms[i + step - 1]].name);
            robots_moving++;
        }
        if (robots_moving > 0)
            printf("\n");
    }
}

void cleanup_maze(maze_t *maze)
{
    int i;
    
    for (i = 0; i < maze->room_count; i++) {
        if (maze->rooms[i].name)
            free(maze->rooms[i].name);
        if (maze->rooms[i].connections)
            free(maze->rooms[i].connections);
    }
}

int main(void)
{
    maze_t maze = {0};
    path_t path;
    
    if (parse_input(&maze) == -1) {
        write(2, "Error: Failed to parse input\n", 29);
        return 84;
    }
    
    if (maze.start_room == -1 || maze.end_room == -1) {
        write(2, "Error: No start or end room found\n", 34);
        cleanup_maze(&maze);
        return 84;
    }
    
    path = find_shortest_path(&maze);
    if (!path.rooms) {
        write(2, "Error: No path found\n", 21);
        cleanup_maze(&maze);
        return 84;
    }
    
    print_output(&maze, &path);
    
    free(path.rooms);
    cleanup_maze(&maze);
    return 0;
}
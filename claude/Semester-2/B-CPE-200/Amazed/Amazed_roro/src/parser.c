/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Input parsing functions
*/

#include "../include/amazed.h"

static int is_comment(const char *line)
{
    return line[0] == '#' && line[1] != '#';
}

static int is_command(const char *line)
{
    return line[0] == '#' && line[1] == '#';
}

static void trim_whitespace(char *str)
{
    char *start = str;
    char *end;
    int i = 0;
    
    while (*start == ' ' || *start == '\t' || *start == '\n')
        start++;
        
    if (*start == 0) {
        str[0] = '\0';
        return;
    }
        
    end = start + my_strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
        *end-- = '\0';
        
    while (start[i]) {
        str[i] = start[i];
        i++;
    }
    str[i] = '\0';
}

static int is_empty_line(const char *line)
{
    int i = 0;
    
    while (line[i]) {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            return 0;
        i++;
    }
    return 1;
}

int parse_number_of_robots(maze_t *maze, char *line)
{
    int count = 0;
    int i = 0;

    while (line[i] >= '0' && line[i] <= '9') {
        count = count * 10 + (line[i] - '0');
        i++;
    }
    
    if (i == 0 || line[i] != '\0')
        return -1;
        
    maze->robot_count = count;
    return 0;
}

int parse_room(maze_t *maze, char *line, int *is_start, int *is_end)
{
    char *name = NULL;
    char *token;
    int x, y;

    token = strtok(line, " \t\n");
    if (!token)
        return -1;
        
    name = my_strdup(token);
    if (!name)
        return -1;
        
    token = strtok(NULL, " \t\n");
    if (!token) {
        free(name);
        return -1;
    }
    x = atoi(token);
    
    token = strtok(NULL, " \t\n");
    if (!token) {
        free(name);
        return -1;
    }
    y = atoi(token);
    
    if (add_room(maze, name, x, y, *is_start, *is_end) == -1) {
        free(name);
        return -1;
    }
    
    free(name);
    *is_start = 0;
    *is_end = 0;
    return 0;
}

int parse_tunnel(maze_t *maze, char *line)
{
    char *room1_name, *room2_name;
    char *dash_pos;
    int room1_id, room2_id;
    tunnel_t *tunnel;

    dash_pos = strchr(line, '-');
    if (!dash_pos)
        return -1;
        
    *dash_pos = '\0';
    room1_name = line;
    room2_name = dash_pos + 1;
    
    while (*room1_name == ' ' || *room1_name == '\t')
        room1_name++;
    while (*room2_name == ' ' || *room2_name == '\t')
        room2_name++;
        
    char *end = room1_name + my_strlen(room1_name) - 1;
    while (end > room1_name && (*end == ' ' || *end == '\t' || *end == '\n'))
        *end-- = '\0';
        
    end = room2_name + my_strlen(room2_name) - 1;
    while (end > room2_name && (*end == ' ' || *end == '\t' || *end == '\n'))
        *end-- = '\0';
    
    room1_id = find_room_by_name(maze, room1_name);
    room2_id = find_room_by_name(maze, room2_name);
    
    if (room1_id == -1 || room2_id == -1)
        return -1;
        
    if (maze->tunnel_count >= MAX_TUNNELS)
        return -1;
        
    tunnel = &maze->tunnels[maze->tunnel_count];
    tunnel->room1 = my_strdup(room1_name);
    tunnel->room2 = my_strdup(room2_name);
    tunnel->room1_id = room1_id;
    tunnel->room2_id = room2_id;
    
    if (!tunnel->room1 || !tunnel->room2) {
        free(tunnel->room1);
        free(tunnel->room2);
        return -1;
    }
    
    add_connection(maze, room1_id, room2_id);
    maze->tunnel_count++;
    
    return 0;
}

int parse_input(maze_t *maze)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_chars;
    int is_start = 0, is_end = 0;
    int parsed_robot_count = 0;

    while ((read_chars = getline(&line, &len, stdin)) != -1) {
        if (read_chars > 0 && line[read_chars - 1] == '\n')
            line[read_chars - 1] = '\0';
            
        trim_whitespace(line);
            
        if (is_empty_line(line))
            break;
            
        if (is_comment(line))
            continue;
            
        if (is_command(line)) {
            if (my_strcmp(line, "##start") == 0) {
                is_start = 1;
                continue;
            } else if (my_strcmp(line, "##end") == 0) {
                is_end = 1;
                continue;
            }
            continue;
        }
        
        if (!parsed_robot_count) {
            if (parse_number_of_robots(maze, line) != 0) {
                free(line);
                return -1;
            }
            parsed_robot_count = 1;
            continue;
        }
        
        if (strchr(line, '-') != NULL) {
            if (parse_tunnel(maze, line) != 0) {
                free(line);
                return -1;
            }
        } else {
            if (parse_room(maze, line, &is_start, &is_end) != 0) {
                free(line);
                return -1;
            }
        }
    }
    
    free(line);
    return 0;
}
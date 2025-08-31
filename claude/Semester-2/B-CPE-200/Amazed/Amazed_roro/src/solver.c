/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Solution generation and robot simulation
*/

#include "../include/amazed.h"

static robot_t *create_robots(maze_t *maze)
{
    robot_t *robots = malloc(sizeof(robot_t) * maze->robot_count);
    int i, path_length;

    if (!robots)
        return NULL;
        
    for (i = 0; i < maze->robot_count; i++) {
        robots[i].id = i + 1;
        robots[i].current_room = maze->start_room;
        robots[i].target_room = -1;
        robots[i].finished = 0;
        robots[i].path_index = 0;
        
        robots[i].path = malloc(sizeof(path_t));
        if (!robots[i].path) {
            for (int j = 0; j < i; j++) {
                free(robots[j].path->rooms);
                free(robots[j].path);
            }
            free(robots);
            return NULL;
        }
        
        robots[i].path->rooms = find_shortest_path(maze, maze->start_room, 
                                                  maze->end_room, &path_length);
        robots[i].path->length = path_length;
        robots[i].path->robot_id = i + 1;
        
        if (!robots[i].path->rooms) {
            for (int j = 0; j <= i; j++) {
                free(robots[j].path->rooms);
                free(robots[j].path);
            }
            free(robots);
            return NULL;
        }
    }
    
    return robots;
}

static int can_move_robot(maze_t *maze, robot_t *robot, int next_room)
{
    int i;

    (void)robot;
    
    if (next_room == maze->end_room || next_room == maze->start_room)
        return 1;
        
    for (i = 0; i < maze->room_count; i++) {
        if (maze->rooms[i].robot_id != -1 && i == next_room)
            return 0;
    }
    
    return 1;
}

static char *create_move_string(robot_t *robot, int room_id, maze_t *maze)
{
    char *move;
    char robot_str[16], room_str[64];
    int len;

    sprintf(robot_str, "P%d-", robot->id);
    strcpy(room_str, maze->rooms[room_id].name);
    
    len = my_strlen(robot_str) + my_strlen(room_str) + 1;
    move = malloc(len);
    if (!move)
        return NULL;
        
    strcpy(move, robot_str);
    strcat(move, room_str);
    
    return move;
}

int simulate_robots(maze_t *maze, solution_t *solution)
{
    int turn = 0;
    int finished_robots = 0;
    int i, moved_count;
    char **turn_moves = malloc(sizeof(char *) * maze->robot_count);
    
    if (!turn_moves)
        return -1;
        
    while (finished_robots < maze->robot_count) {
        moved_count = 0;
        
        for (i = 0; i < maze->robot_count; i++) {
            robot_t *robot = &solution->robots[i];
            
            if (robot->finished)
                continue;
                
            if (robot->path_index + 1 >= robot->path->length) {
                robot->finished = 1;
                finished_robots++;
                continue;
            }
            
            int next_room = robot->path->rooms[robot->path_index + 1];
            
            if (can_move_robot(maze, robot, next_room)) {
                if (robot->current_room != maze->start_room)
                    maze->rooms[robot->current_room].robot_id = -1;
                    
                robot->current_room = next_room;
                robot->path_index++;
                
                if (next_room != maze->end_room)
                    maze->rooms[next_room].robot_id = robot->id;
                    
                turn_moves[moved_count] = create_move_string(robot, next_room, maze);
                moved_count++;
                
                if (next_room == maze->end_room) {
                    robot->finished = 1;
                    finished_robots++;
                }
            }
        }
        
        if (moved_count > 0) {
            solution->moves = realloc(solution->moves, 
                                    sizeof(char *) * (solution->move_count + moved_count));
            if (!solution->moves) {
                free(turn_moves);
                return -1;
            }
            
            for (i = 0; i < moved_count; i++) {
                solution->moves[solution->move_count + i] = turn_moves[i];
            }
            solution->move_count += moved_count;
        }
        
        turn++;
        if (turn > 1000)
            break;
    }
    
    solution->total_turns = turn;
    free(turn_moves);
    return 0;
}

solution_t *solve_maze(maze_t *maze)
{
    solution_t *solution = malloc(sizeof(solution_t));
    
    if (!solution)
        return NULL;
        
    solution->robots = create_robots(maze);
    if (!solution->robots) {
        free(solution);
        return NULL;
    }
    
    solution->robot_count = maze->robot_count;
    solution->total_turns = 0;
    solution->moves = NULL;
    solution->move_count = 0;
    
    if (simulate_robots(maze, solution) != 0) {
        cleanup_solution(solution);
        return NULL;
    }
    
    return solution;
}

void cleanup_solution(solution_t *solution)
{
    int i;

    if (!solution)
        return;
        
    if (solution->robots) {
        for (i = 0; i < solution->robot_count; i++) {
            free(solution->robots[i].path->rooms);
            free(solution->robots[i].path);
        }
        free(solution->robots);
    }
    
    if (solution->moves) {
        for (i = 0; i < solution->move_count; i++)
            free(solution->moves[i]);
        free(solution->moves);
    }
    
    free(solution);
}
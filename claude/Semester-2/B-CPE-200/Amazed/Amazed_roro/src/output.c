/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Output formatting functions
*/

#include "../include/amazed.h"

void print_maze_description(maze_t *maze)
{
    int i;

    printf("#number_of_robots\n");
    printf("%d\n", maze->robot_count);
    
    printf("#rooms\n");
    for (i = 0; i < maze->room_count; i++) {
        room_t *room = &maze->rooms[i];
        if (room->is_start)
            printf("##start\n");
        if (room->is_end)
            printf("##end\n");
        printf("%s %d %d\n", room->name, room->x, room->y);
    }
    
    printf("#tunnels\n");
    for (i = 0; i < maze->tunnel_count; i++) {
        tunnel_t *tunnel = &maze->tunnels[i];
        printf("%s-%s\n", tunnel->room1, tunnel->room2);
    }
}

static void print_moves_for_turn(solution_t *solution, int turn_start, int turn_end)
{
    int i;

    for (i = turn_start; i < turn_end; i++) {
        printf("%s", solution->moves[i]);
        if (i < turn_end - 1)
            printf(" ");
    }
    printf("\n");
}

void print_solution(maze_t *maze, solution_t *solution)
{
    int i, move_index = 0;
    int turn = 0;
    int *robots_moved = malloc(sizeof(int) * maze->robot_count);

    (void)maze;
    
    if (!robots_moved)
        return;
        
    printf("#moves\n");
    
    while (move_index < solution->move_count) {
        int turn_start = move_index;
        int moves_this_turn = 0;
        
        for (i = 0; i < maze->robot_count; i++)
            robots_moved[i] = 0;
            
        while (move_index < solution->move_count) {
            char *move = solution->moves[move_index];
            int robot_id = 0;
            
            if (move[0] == 'P') {
                robot_id = atoi(&move[1]) - 1;
                if (robot_id >= 0 && robot_id < maze->robot_count && 
                    !robots_moved[robot_id]) {
                    robots_moved[robot_id] = 1;
                    moves_this_turn++;
                    move_index++;
                } else {
                    break;
                }
            } else {
                move_index++;
            }
        }
        
        if (moves_this_turn > 0) {
            print_moves_for_turn(solution, turn_start, turn_start + moves_this_turn);
            turn++;
        }
        
        if (move_index == turn_start)
            break;
    }
    
    free(robots_moved);
}
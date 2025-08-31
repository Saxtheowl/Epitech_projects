/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Main function for amazed maze solver
*/

#include "../include/amazed.h"

int main(void)
{
    maze_t *maze;
    solution_t *solution;

    maze = create_maze();
    if (!maze)
        return 84;
        
    if (parse_input(maze) != 0) {
        cleanup_maze(maze);
        return 84;
    }
    
    if (maze->start_room == -1 || maze->end_room == -1) {
        print_error("No start or end room defined");
        cleanup_maze(maze);
        return 84;
    }
    
    create_adjacency_matrix(maze);
    
    solution = solve_maze(maze);
    if (!solution) {
        cleanup_maze(maze);
        return 84;
    }
    
    print_maze_description(maze);
    print_solution(maze, solution);
    
    cleanup_solution(solution);
    cleanup_maze(maze);
    
    return 0;
}
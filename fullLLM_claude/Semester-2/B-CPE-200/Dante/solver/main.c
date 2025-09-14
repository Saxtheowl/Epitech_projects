#include "solver.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <maze_file>\n", argv[0]);
        return 84;
    }
    
    maze_t *maze = load_maze(argv[1]);
    if (!maze) {
        fprintf(stderr, "Error: Could not load maze from file %s\n", argv[1]);
        return 84;
    }
    
    if (solve_maze(maze)) {
        print_maze(maze);
        free_maze(maze);
        return 0;
    } else {
        printf("no solution found\n");
        free_maze(maze);
        return 0;
    }
}
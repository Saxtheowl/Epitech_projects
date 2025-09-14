#include "generator.h"

int main(int argc, char **argv)
{
    int width, height, perfect = 0;
    maze_t *maze;
    
    if (argc < 3 || argc > 4) {
        fprintf(stderr, "Usage: %s x y [perfect]\n", argv[0]);
        return 84;
    }
    
    width = atoi(argv[1]);
    height = atoi(argv[2]);
    
    if (width <= 0 || height <= 0) {
        fprintf(stderr, "Error: Invalid maze dimensions\n");
        return 84;
    }
    
    if (argc == 4 && strcmp(argv[3], "perfect") == 0) {
        perfect = 1;
    }
    
    srand(time(NULL));
    
    maze = create_maze(width, height, perfect);
    if (!maze) {
        fprintf(stderr, "Error: Could not create maze\n");
        return 84;
    }
    
    if (perfect) {
        generate_perfect_maze(maze);
    } else {
        generate_imperfect_maze(maze);
    }
    
    print_maze(maze);
    free_maze(maze);
    
    return 0;
}
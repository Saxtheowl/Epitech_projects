#include "my_sokoban.h"

void print_usage(void)
{
    printf("USAGE\n");
    printf("    ./my_sokoban map\n");
    printf("DESCRIPTION\n");
    printf("    map file representing the warehouse map, containing '#' for walls,\n");
    printf("    'P' for the player, 'X' for boxes and 'O' for storage locations.\n");
}

int main(int ac, char **av)
{
    map_t *map;
    
    if (ac == 2 && strcmp(av[1], "-h") == 0) {
        print_usage();
        return 0;
    }
    
    if (ac != 2) {
        print_usage();
        return 84;
    }
    
    map = load_map(av[1]);
    if (!map) {
        fprintf(stderr, "Error: Invalid map file\n");
        return 84;
    }
    
    if (validate_map(map) != 0) {
        fprintf(stderr, "Error: Invalid map\n");
        free_map(map);
        return 84;
    }
    
    if (init_ncurses() != 0) {
        fprintf(stderr, "Error: Failed to initialize ncurses\n");
        free_map(map);
        return 84;
    }
    
    game_loop(map);
    
    cleanup_ncurses();
    free_map(map);
    
    return 0;
}
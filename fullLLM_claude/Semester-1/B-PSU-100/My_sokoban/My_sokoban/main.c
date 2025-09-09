#include "sokoban.h"

static void print_usage(void)
{
    my_putstr("USAGE\n");
    my_putstr("    ./my_sokoban map\n");
    my_putstr("DESCRIPTION\n");
    my_putstr("    map    file representing the warehouse map, containing '#' for walls,\n");
    my_putstr("           'P' for the player, 'X' for boxes and 'O' for storage locations.\n");
}

int main(int ac, char **av)
{
    sokoban_map_t *map;
    int result;

    if (ac == 2 && my_strlen(av[1]) == 2 && av[1][0] == '-' && av[1][1] == 'h') {
        print_usage();
        return 0;
    }
    if (ac != 2) {
        print_usage();
        return 84;
    }
    
    map = load_map(av[1]);
    if (!map) {
        return 84;
    }
    
    if (!is_valid_map(map)) {
        free_map(map);
        return 84;
    }
    
    result = game_loop(map);
    free_map(map);
    
    return result;
}
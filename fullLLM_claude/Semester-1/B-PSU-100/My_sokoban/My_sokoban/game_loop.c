#include "sokoban.h"


static char *map_to_string(sokoban_map_t *original_map)
{
    int total_size = 0;
    int i, j, k = 0;
    char *str;
    
    for (i = 0; i < original_map->height; i++)
        total_size += my_strlen(original_map->map[i]) + 1;
    
    str = malloc(total_size + 1);
    if (!str)
        return NULL;
    
    for (i = 0; i < original_map->height; i++) {
        for (j = 0; original_map->map[i][j]; j++)
            str[k++] = original_map->map[i][j];
        str[k++] = '\n';
    }
    str[k] = '\0';
    
    return str;
}

int game_loop(sokoban_map_t *map)
{
    int input;
    int game_over = 0;
    int result = 0;
    char *original_map_str;
    sokoban_map_t *original_map;
    
    original_map = make_map_from_string("");
    if (!original_map)
        return 84;
    
    free_map(original_map);
    original_map_str = map_to_string(map);
    if (!original_map_str)
        return 84;
    
    init_ncurses();
    
    while (!game_over) {
        display_map(map);
        
        if (check_win_condition(map)) {
            display_map(map);
            cleanup_ncurses();
            free(original_map_str);
            return 0;
        }
        
        if (check_lose_condition(map)) {
            display_map(map);
            cleanup_ncurses();
            free(original_map_str);
            return 1;
        }
        
        input = handle_input();
        
        switch (input) {
            case 1:
                move_player(map, 0, -1);
                break;
            case 2:
                move_player(map, 0, 1);
                break;
            case 3:
                move_player(map, -1, 0);
                break;
            case 4:
                move_player(map, 1, 0);
                break;
            case 5:
                free_map(map);
                map = make_map_from_string(original_map_str);
                if (!map) {
                    cleanup_ncurses();
                    free(original_map_str);
                    return 84;
                }
                break;
            case -1:
                game_over = 1;
                result = 0;
                break;
        }
    }
    
    cleanup_ncurses();
    free(original_map_str);
    return result;
}
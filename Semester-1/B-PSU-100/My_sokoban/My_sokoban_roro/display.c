#include "my_sokoban.h"

int init_ncurses(void)
{
    printf("Sokoban Game (Simple Terminal Version)\n");
    printf("Use: w/a/s/d for movement, space to reset, q to quit\n\n");
    return 0;
}

void cleanup_ncurses(void)
{
    printf("\nGame ended.\n");
}

void display_map(map_t *map)
{
    if (!map || !map->grid)
        return;
    
    printf("\033[2J\033[H");
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            printf("%c", map->grid[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

void display_message(char *message)
{
    if (!message)
        return;
    
    printf("\033[2J\033[H");
    printf("%s\n", message);
}

int check_terminal_size(map_t *map)
{
    (void)map;
    return 0;
}
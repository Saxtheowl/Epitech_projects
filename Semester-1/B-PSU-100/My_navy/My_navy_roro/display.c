#include "my_navy.h"

void print_grid(char grid[GRID_SIZE][GRID_SIZE], char *title)
{
    my_putstr(title);
    my_putstr(":\n|A B C D E F G H\n-+---------------\n");
    
    for (int y = 0; y < GRID_SIZE; y++) {
        my_putchar('1' + y);
        my_putchar('|');
        for (int x = 0; x < GRID_SIZE; x++) {
            my_putchar(grid[y][x]);
            if (x < GRID_SIZE - 1)
                my_putchar(' ');
        }
        my_putchar('\n');
    }
}

void print_game_state(void)
{
    print_grid(g_game.my_grid, "my navy");
    print_grid(g_game.enemy_grid, "enemy navy");
}
#include "my_navy.h"

void display_help(void)
{
    my_putstr("USAGE\n");
    my_putstr("     ./my_navy [first_player_pid] navy_positions\n");
    my_putstr("DESCRIPTION\n");
    my_putstr("     first_player_pid: only for the 2nd player. pid of the first player.\n");
    my_putstr("     navy_positions: file representing the positions of the ships.\n");
}

void init_game_state(void)
{
    int i, j, k;
    
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            g_game.grid[i][j] = 0;
            g_game.enemy_grid[i][j] = 0;
        }
    }
    
    for (i = 0; i < g_game.ship_count; i++) {
        ship_t *ship = &g_game.ships[i];
        int dx = (ship->end_x > ship->start_x) ? 1 : (ship->end_x < ship->start_x) ? -1 : 0;
        int dy = (ship->end_y > ship->start_y) ? 1 : (ship->end_y < ship->start_y) ? -1 : 0;
        
        for (k = 0; k < ship->length; k++) {
            int x = ship->start_x + k * dx;
            int y = ship->start_y + k * dy;
            g_game.grid[x][y] = ship->length;
        }
    }
    
    g_game.game_over = 0;
    g_game.i_won = 0;
    g_game.total_hits_received = 0;
    g_game.total_hits_made = 0;
}

void display_grids(void)
{
    int i, j;
    
    my_putstr("my navy:\n |A B C D E F G H\n-+---------------\n");
    
    for (i = 0; i < GRID_SIZE; i++) {
        my_put_nbr(i + 1);
        my_putstr("|");
        
        for (j = 0; j < GRID_SIZE; j++) {
            if (g_game.grid[i][j] > 0) {
                if (g_game.grid[i][j] < 0) {
                    my_putstr("x ");
                } else {
                    my_put_nbr(g_game.grid[i][j]);
                    my_putstr(" ");
                }
            } else if (g_game.grid[i][j] == -1) {
                my_putstr("o ");
            } else {
                my_putstr(". ");
            }
        }
        my_putstr("\n");
    }
    
    my_putstr("enemy navy:\n |A B C D E F G H\n-+---------------\n");
    
    for (i = 0; i < GRID_SIZE; i++) {
        my_put_nbr(i + 1);
        my_putstr("|");
        
        for (j = 0; j < GRID_SIZE; j++) {
            if (g_game.enemy_grid[i][j] == 1) {
                my_putstr("x ");
            } else if (g_game.enemy_grid[i][j] == -1) {
                my_putstr("o ");
            } else {
                my_putstr(". ");
            }
        }
        my_putstr("\n");
    }
}
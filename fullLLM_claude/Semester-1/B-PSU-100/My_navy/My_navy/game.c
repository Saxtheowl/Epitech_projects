#include "my_navy.h"

int process_attack(int x, int y)
{
    if (g_game.grid[x][y] > 0) {
        int ship_length = g_game.grid[x][y];
        g_game.grid[x][y] = -ship_length;
        
        int i;
        for (i = 0; i < g_game.ship_count; i++) {
            if (g_game.ships[i].length == ship_length) {
                g_game.ships[i].hits++;
                break;
            }
        }
        
        g_game.total_hits_received++;
        return 1;
    } else {
        g_game.grid[x][y] = -1;
        return 0;
    }
}

int count_remaining_ship_parts(void)
{
    int total_parts = 0;
    int i;
    
    for (i = 0; i < g_game.ship_count; i++) {
        total_parts += g_game.ships[i].length - g_game.ships[i].hits;
    }
    
    return total_parts;
}

int all_ships_sunk(void)
{
    return count_remaining_ship_parts() == 0;
}

void get_player_attack(int *x, int *y)
{
    char buffer[10];
    char c;
    int i = 0;
    
    do {
        my_putstr("attack: ");
        i = 0;
        
        while ((c = getchar()) != '\n' && c != EOF && i < 9) {
            buffer[i++] = c;
        }
        buffer[i] = '\0';
        
        if (i == 0)
            continue;
        
        if (!parse_coordinate(buffer, x, y)) {
            my_putstr("wrong position\n");
            continue;
        }
        
        break;
    } while (1);
}

void game_loop(void)
{
    int x, y, result;
    
    while (!g_game.game_over) {
        display_grids();
        
        if (g_game.is_my_turn) {
            get_player_attack(&x, &y);
            
            if (send_coordinates(x, y) == -1) {
                g_game.game_over = 1;
                continue;
            }
            
            result = receive_result();
            
            my_putstr("result: ");
            my_putchar('A' + y);
            my_put_nbr(x + 1);
            my_putstr(result ? ":hit\n" : ":missed\n");
            
            g_game.enemy_grid[x][y] = result ? 1 : -1;
            g_game.total_hits_made += result;
            
            if (g_game.total_hits_made == 14) {
                my_putstr("I won\n");
                g_game.i_won = 1;
                g_game.game_over = 1;
                continue;
            }
            
            my_putstr("waiting for enemy's attack...\n");
            g_game.is_my_turn = 0;
            
        } else {
            if (receive_coordinates(&x, &y) == -1) {
                g_game.game_over = 1;
                continue;
            }
            
            result = process_attack(x, y);
            
            if (send_result(result) == -1) {
                g_game.game_over = 1;
                continue;
            }
            
            my_putstr("result: ");
            my_putchar('A' + y);
            my_put_nbr(x + 1);
            my_putstr(result ? ":hit\n" : ":missed\n");
            
            if (all_ships_sunk()) {
                display_grids();
                my_putstr("Enemy won\n");
                g_game.i_won = 0;
                g_game.game_over = 1;
                continue;
            }
            
            g_game.is_my_turn = 1;
        }
    }
}
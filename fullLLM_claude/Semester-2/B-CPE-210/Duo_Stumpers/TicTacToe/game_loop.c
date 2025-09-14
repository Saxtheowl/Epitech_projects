#include "tictactoe.h"

void game_loop(game_t *game)
{
    int x, y;
    
    while (1) {
        display_grid(game);
        
        if (get_move(game, &x, &y) != 0) {
            continue;
        }
        
        if (make_move(game, x, y) != 0) {
            continue;
        }
        
        if (check_winner(game)) {
            display_grid(game);
            printf("Player %d won!\n", game->current_player);
            return;
        }
        
        if (is_grid_full(game)) {
            display_grid(game);
            printf("It's a tie!\n");
            return;
        }
        
        game->current_player = (game->current_player == 1) ? 2 : 1;
    }
}
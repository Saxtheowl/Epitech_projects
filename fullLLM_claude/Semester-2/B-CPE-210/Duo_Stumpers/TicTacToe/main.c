#include "tictactoe.h"

int main(int ac, char **av)
{
    game_t game;
    
    game.size = 3;
    game.player1_char = 'X';
    game.player2_char = 'O';
    game.current_player = 1;
    
    if (parse_args(ac, av, &game) != 0) {
        fprintf(stderr, "Invalid arguments\n");
        return 84;
    }
    
    if (game.player1_char == game.player2_char) {
        fprintf(stderr, "Players cannot use the same symbol\n");
        return 84;
    }
    
    if (init_game(&game) != 0) {
        fprintf(stderr, "Failed to initialize game\n");
        return 84;
    }
    
    game_loop(&game);
    
    free_game(&game);
    return 0;
}
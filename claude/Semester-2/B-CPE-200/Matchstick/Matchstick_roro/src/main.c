/*
** EPITECH PROJECT, 2024
** Matchstick
** File description:
** Main function for matchstick game
*/

#include "../include/matchstick.h"

static int game_loop(game_t *game)
{
    int line, matches;
    
    while (!is_game_over(game)) {
        display_board(game);
        
        if (game->current_player == 0) {
            printf("\nYour turn:\n");
            line = get_player_line();
            if (line == -1)
                continue;
            matches = get_player_matches();
            if (matches == -1)
                continue;
                
            if (validate_move(game, line, matches) == 0) {
                make_move(game, line, matches);
                game->current_player = 1;
            }
        } else {
            printf("\nAI's turn...\n");
            ai_move(game);
            game->current_player = 0;
        }
    }
    
    display_board(game);
    
    if (game->current_player == 0) {
        printf("You lost, too bad...\n");
        return 2;
    } else {
        printf("I lost... snif... but I'll get you next time!!\n");
        return 1;
    }
}

int main(int argc, char **argv)
{
    game_t *game;
    int lines, max_matches, result;

    if (check_arguments(argc, argv) != 0)
        return 84;
        
    lines = my_atoi(argv[1]);
    max_matches = my_atoi(argv[2]);
    
    if (lines < MIN_LINES || lines >= MAX_LINES || max_matches <= 0) {
        print_error("Invalid parameters");
        return 84;
    }
    
    game = init_game(lines, max_matches);
    if (!game)
        return 84;
        
    srandom(time(NULL) + getpid());
    
    result = game_loop(game);
    cleanup_game(game);
    
    return result;
}
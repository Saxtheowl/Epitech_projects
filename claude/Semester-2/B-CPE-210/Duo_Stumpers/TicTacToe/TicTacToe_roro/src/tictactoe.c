/*
** EPITECH PROJECT, 2025
** TicTacToe
** File description:
** tictactoe
*/

#include "tictactoe.h"

int tictactoe(int argc, char **argv)
{
    args_t args;
    game_t *game = NULL;
    int x = 0;
    int y = 0;

    if (parse_arguments(argc, argv, &args) != 0) {
        write(STDERR_FILENO, "Invalid arguments\n", 18);
        return 84;
    }
    game = init_game(&args);
    if (!game)
        return 84;
    display_grid(game);
    while (1) {
        if (get_player_move(game, &x, &y) != 0) {
            free_game(game);
            return 84;
        }
        if (make_move(game, x, y) != 0)
            continue;
        display_grid(game);
        if (check_win(game)) {
            printf("Player %d won!\n", game->current_player);
            free_game(game);
            return 0;
        }
        if (is_grid_full(game)) {
            printf("It's a tie!\n");
            free_game(game);
            return 0;
        }
        game->current_player = (game->current_player == 1) ? 2 : 1;
    }
    free_game(game);
    return 0;
}
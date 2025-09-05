/*
** EPITECH PROJECT, 2025
** TicTacToe
** File description:
** test_tictactoe
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "tictactoe.h"

Test(tictactoe, parse_arguments_valid)
{
    char *argv[] = {"tictactoe", "-p1", "A", "-p2", "B", "-s", "4"};
    args_t args;
    
    int result = parse_arguments(7, argv, &args);
    cr_assert_eq(result, 0);
    cr_assert_eq(args.player1_char, 'A');
    cr_assert_eq(args.player2_char, 'B');
    cr_assert_eq(args.grid_size, 4);
}

Test(tictactoe, parse_arguments_same_chars)
{
    char *argv[] = {"tictactoe", "-p1", "X", "-p2", "X"};
    args_t args;
    
    int result = parse_arguments(5, argv, &args);
    cr_assert_eq(result, 84);
}

Test(tictactoe, init_game_basic)
{
    args_t args = {'X', 'O', 3};
    game_t *game = init_game(&args);
    
    cr_assert_not_null(game);
    cr_assert_eq(game->size, 3);
    cr_assert_eq(game->player1_char, 'X');
    cr_assert_eq(game->player2_char, 'O');
    cr_assert_eq(game->current_player, 1);
    free_game(game);
}

Test(tictactoe, make_move_valid)
{
    args_t args = {'X', 'O', 3};
    game_t *game = init_game(&args);
    
    int result = make_move(game, 1, 1);
    cr_assert_eq(result, 0);
    cr_assert_eq(game->grid[1][1], 'X');
    free_game(game);
}
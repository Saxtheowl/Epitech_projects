/*
** EPITECH PROJECT, 2025
** Gomoku_roro tests
** File description:
**   AI win/block behavior
*/

#include <criterion/criterion.h>
#include "gomoku.h"

Test(ai, play_winning_move_horizontal)
{
    gomoku_t g;
    int x;
    int y;

    cr_assert_eq(board_init(&g, 10), 0);
    board_set(&g, 0, 2, 1);
    board_set(&g, 1, 2, 1);
    board_set(&g, 2, 2, 1);
    board_set(&g, 3, 2, 1);
    ai_pick_move(&g, &x, &y);
    cr_assert_eq(x, 4);
    cr_assert_eq(y, 2);
    board_free(&g);
}

Test(ai, block_opponent_horizontal)
{
    gomoku_t g;
    int x;
    int y;

    cr_assert_eq(board_init(&g, 10), 0);
    board_set(&g, 0, 5, 2);
    board_set(&g, 1, 5, 2);
    board_set(&g, 2, 5, 2);
    board_set(&g, 3, 5, 2);
    ai_pick_move(&g, &x, &y);
    cr_assert_eq(x, 4);
    cr_assert_eq(y, 5);
    board_free(&g);
}


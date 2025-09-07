/*
** EPITECH PROJECT, 2025
** Gomoku_roro tests
** File description:
**   AI win/block vertical/diagonal
*/

#include <criterion/criterion.h>
#include "gomoku.h"

Test(ai, play_winning_move_vertical)
{
    gomoku_t g;
    int x;
    int y;

    cr_assert_eq(board_init(&g, 10), 0);
    board_set(&g, 4, 0, 1);
    board_set(&g, 4, 1, 1);
    board_set(&g, 4, 2, 1);
    board_set(&g, 4, 3, 1);
    ai_pick_move(&g, &x, &y);
    cr_assert_eq(x, 4);
    cr_assert_eq(y, 4);
    board_free(&g);
}

Test(ai, play_winning_move_diag_down)
{
    gomoku_t g;
    int x;
    int y;

    cr_assert_eq(board_init(&g, 10), 0);
    board_set(&g, 1, 1, 1);
    board_set(&g, 2, 2, 1);
    board_set(&g, 3, 3, 1);
    board_set(&g, 4, 4, 1);
    ai_pick_move(&g, &x, &y);
    /* Accept either end: (5,5) or (0,0) */
    cr_assert(((x == 5) && (y == 5)) || ((x == 0) && (y == 0)));
    board_free(&g);
}

Test(ai, block_opponent_diag_up)
{
    gomoku_t g;
    int x;
    int y;

    cr_assert_eq(board_init(&g, 10), 0);
    board_set(&g, 1, 8, 2);
    board_set(&g, 2, 7, 2);
    board_set(&g, 3, 6, 2);
    board_set(&g, 4, 5, 2);
    ai_pick_move(&g, &x, &y);
    /* Accept either block: (5,4) or (0,9) */
    cr_assert(((x == 5) && (y == 4)) || ((x == 0) && (y == 9)));
    board_free(&g);
}

/*
** EPITECH PROJECT, 2025
** Connect4
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "connect4.h"

static const char *R = "R";
static const char *Y = "Y";

Test(connect4, validate_and_winner)
{
    const char *board =
        "......."
        "......."
        "......."
        "......."
        "RRRR..."
        "YYYY...";
    cr_assert(validate_board(board));
    cr_assert_eq(check_winner(board), 'R');
}

Test(connect4, invalid_float)
{
    const char *board =
        "......."
        "....R.."
        "...R..."
        "..R...."
        ".R....."
        ".......";
    cr_assert_not(validate_board(board));
}

Test(connect4, diagonal_win)
{
    const char *board =
        "......."
        "......."
        "...R..."
        "..YR..."
        ".Y.Y..."
        "Y..Y...";
    cr_assert(validate_board(board));
    cr_assert_eq(check_winner(board), 'Y');
}

Test(connect4, draw_board)
{
    /* full board with no winner */
    const char *board =
        "RYYRYYR"
        "YYRYYRY"
        "RYYRYYR"
        "YYRYYRY"
        "RYYRYYR"
        "YYRYYRY";
    cr_assert(validate_board(board));
    cr_assert_eq(check_winner(board), 0);
}

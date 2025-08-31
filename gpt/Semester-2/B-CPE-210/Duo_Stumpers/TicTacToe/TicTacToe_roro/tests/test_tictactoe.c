/*
** EPITECH PROJECT, 2025
** TicTacToe
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "tictactoe.h"

Test(tictactoe, winners)
{
    cr_assert_eq(check_winner("XXXOO...."), 'X');
    cr_assert_eq(check_winner("X.OX.OX.O"), 'O');
    cr_assert_eq(check_winner("X..XO.OX."), 0);
}

Test(tictactoe, validate)
{
    cr_assert(validate_board("XOXOXO..X"));
    cr_assert_not(validate_board("XXXXXXXXX"));
}


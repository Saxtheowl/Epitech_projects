/*
** EPITECH PROJECT, 2025
** Matchstick
** File description:
** Tests for board helpers
*/

#include <criterion/criterion.h>
#include "matchstick.h"

Test(board, init_and_remove)
{
    board_t *b = board_create(3, 2);
    cr_assert_not_null(b);
    cr_assert_eq(count_line_matches(b, 1), 1);
    cr_assert_eq(count_line_matches(b, 2), 3);
    cr_assert(remove_matches(b, 2, 2));
    cr_assert_eq(count_line_matches(b, 2), 1);
    board_destroy(b);
}

Test(board, invalid_removals)
{
    board_t *b = board_create(3, 1);
    cr_assert_not(remove_matches(b, 0, 1));
    cr_assert_not(remove_matches(b, 4, 1));
    cr_assert_not(remove_matches(b, 1, 0));
    /* more than available on line */
    cr_assert_not(remove_matches(b, 1, 5));
    board_destroy(b);
}

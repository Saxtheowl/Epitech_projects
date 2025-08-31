/*
** EPITECH PROJECT, 2025
** Matchstick
** File description:
** Game helper tests
*/

#include <criterion/criterion.h>
#include "matchstick.h"

Test(game, is_finished_logic)
{
    board_t *b = board_create(2, 3);
    cr_assert_not(is_finished(b));
    /* remove all matches */
    cr_assert(remove_matches(b, 1, count_line_matches(b, 1)));
    cr_assert(remove_matches(b, 2, count_line_matches(b, 2)));
    cr_assert(is_finished(b));
    board_destroy(b);
}

Test(game, parse_args)
{
    int lines; int maxr;
    char *okv[] = {"prog", "4", "3", NULL};
    char *badv1[] = {"prog", "0", "3", NULL};
    char *badv2[] = {"prog", "4", "0", NULL};
    cr_assert(parse_args(3, okv, &lines, &maxr));
    cr_assert_eq(lines, 4);
    cr_assert_eq(maxr, 3);
    cr_assert_not(parse_args(3, badv1, &lines, &maxr));
    cr_assert_not(parse_args(3, badv2, &lines, &maxr));
}


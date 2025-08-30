/*
** EPITECH PROJECT, 2025
** Rush1_roro
** File description:
** Minimal tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "rush.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
}

Test(draw, w1h1, .init = redirect_all_stdout)
{
    pattern_t p = { 'o', 'o', 'o', 'o', '-', '|' };
    draw_rect(1, 1, p);
    cr_assert_stdout_eq_str("o\n");
}

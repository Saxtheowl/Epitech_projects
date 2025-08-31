/*
** EPITECH PROJECT, 2025
** Wolfram_roro
** File description:
** basic tests
*/

#include <criterion/criterion.h>
#include "wolfram.h"

Test(parse, invalid_missing)
{
    args_t cfg;
    const char *av1[] = {"wolfram", "--rule", "30", NULL};
    const char *av2[] = {"wolfram", "--lines", "10", NULL};
    cr_assert_not_eq(parse_args(3, av1, &cfg), 0);
    cr_assert_not_eq(parse_args(3, av2, &cfg), 0);
}

Test(parse, valid)
{
    args_t cfg;
    const char *av[] = {"wolfram", "--rule", "30", "--lines", "5",
        "--start", "2", "--window", "20", NULL};
    cr_assert_eq(parse_args(9, av, &cfg), 0);
    cr_assert_eq(cfg.rule, 30);
    cr_assert_eq(cfg.lines, 5);
    cr_assert_eq(cfg.start, 2);
    cr_assert_eq(cfg.window, 20);
}

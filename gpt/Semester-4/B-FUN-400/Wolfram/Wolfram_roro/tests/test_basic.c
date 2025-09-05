/*
** EPITECH PROJECT, 2025
** Wolfram_roro
** File description:
** test_basic.c
*/

#include <criterion/criterion.h>
#include "wolfram.h"

Test(parse, bad_usage)
{
    Config c;
    char *av[] = {"wolfram", "--rule"};
    cr_assert_eq(parse_args(2, av, &c), 84);
}

Test(parse, ok_minimal)
{
    Config c;
    char *av[] = {"wolfram", "--rule", "30", "--lines", "1"};
    cr_assert_eq(parse_args(5, av, &c), 0);
    cr_assert_eq(c.rule, 30);
    cr_assert_eq(c.lines, 1);
}


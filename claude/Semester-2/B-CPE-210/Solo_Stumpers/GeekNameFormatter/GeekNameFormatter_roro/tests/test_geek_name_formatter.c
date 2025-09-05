/*
** EPITECH PROJECT, 2025
** GeekNameFormatter
** File description:
** Unit tests for geek name formatter
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "geek_name_formatter.h"

Test(geek_name_formatter, test_replace_geek_char)
{
    cr_assert_eq(replace_geek_char('o'), '0');
    cr_assert_eq(replace_geek_char('O'), '0');
    cr_assert_eq(replace_geek_char('i'), '1');
    cr_assert_eq(replace_geek_char('I'), '1');
    cr_assert_eq(replace_geek_char('u'), '2');
    cr_assert_eq(replace_geek_char('U'), '2');
    cr_assert_eq(replace_geek_char('e'), '3');
    cr_assert_eq(replace_geek_char('E'), '3');
    cr_assert_eq(replace_geek_char('a'), '4');
    cr_assert_eq(replace_geek_char('A'), '4');
    cr_assert_eq(replace_geek_char('y'), '5');
    cr_assert_eq(replace_geek_char('Y'), '5');
    cr_assert_eq(replace_geek_char('z'), 'z');
}

Test(geek_name_formatter, test_to_upper)
{
    cr_assert_eq(to_upper('a'), 'A');
    cr_assert_eq(to_upper('z'), 'Z');
    cr_assert_eq(to_upper('A'), 'A');
    cr_assert_eq(to_upper('Z'), 'Z');
}

Test(geek_name_formatter, test_to_lower)
{
    cr_assert_eq(to_lower('A'), 'a');
    cr_assert_eq(to_lower('Z'), 'z');
    cr_assert_eq(to_lower('a'), 'a');
    cr_assert_eq(to_lower('z'), 'z');
}
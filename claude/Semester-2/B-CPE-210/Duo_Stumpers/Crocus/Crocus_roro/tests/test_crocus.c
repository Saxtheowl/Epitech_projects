/*
** EPITECH PROJECT, 2025
** Crocus
** File description:
** test_crocus
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "crocus.h"

Test(crocus, parse_arguments_valid)
{
    char *argv[] = {"crocus", "-n", "123", "-s", "abc"};
    args_t args;
    
    int result = parse_arguments(5, argv, &args);
    cr_assert_eq(result, 0);
    cr_assert_str_eq(args.number, "123");
    cr_assert_str_eq(args.string, "abc");
}

Test(crocus, parse_arguments_no_number)
{
    char *argv[] = {"crocus", "-s", "abc"};
    args_t args;
    
    int result = parse_arguments(3, argv, &args);
    cr_assert_eq(result, 84);
}

Test(crocus, is_valid_number_valid)
{
    cr_assert_eq(is_valid_number("123"), 1);
    cr_assert_eq(is_valid_number("0"), 1);
    cr_assert_eq(is_valid_number("9876543210"), 1);
}

Test(crocus, is_valid_number_invalid)
{
    cr_assert_eq(is_valid_number("abc"), 0);
    cr_assert_eq(is_valid_number("12a3"), 0);
    cr_assert_eq(is_valid_number(""), 0);
}
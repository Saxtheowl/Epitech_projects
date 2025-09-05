/*
** EPITECH PROJECT, 2025
** Fractals
** File description:
** test_fractals
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "fractals.h"

Test(fractals, parse_pattern_basic)
{
    pattern_t pattern = parse_pattern("##@#.");
    
    cr_assert_eq(pattern.width, 2);
    cr_assert_eq(pattern.height, 2);
    cr_assert_str_eq(pattern.data, "####.");
    free_pattern(&pattern);
}

Test(fractals, parse_arguments_valid)
{
    char *argv[] = {"fractals", "1", "##@#.", "..@.."};
    int iterations;
    pattern_t sharp_pattern, dot_pattern;
    
    int result = parse_arguments(4, argv, &iterations, &sharp_pattern, &dot_pattern);
    cr_assert_eq(result, 0);
    cr_assert_eq(iterations, 1);
    free_pattern(&sharp_pattern);
    free_pattern(&dot_pattern);
}

Test(fractals, my_atoi_valid)
{
    cr_assert_eq(my_atoi("0"), 0);
    cr_assert_eq(my_atoi("42"), 42);
    cr_assert_eq(my_atoi("123"), 123);
}

Test(fractals, my_atoi_invalid)
{
    cr_assert_eq(my_atoi("abc"), -1);
    cr_assert_eq(my_atoi("1a2"), -1);
}
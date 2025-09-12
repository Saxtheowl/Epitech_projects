/*
** EPITECH PROJECT, 2024
** Day02 - Bootcamp Phoenix
** File description:
** Unit tests for my_strncmp function using Criterion
*/

#include <criterion/criterion.h>
#include <string.h>

int my_strncmp(char const *s1, char const *s2, int n);

Test(my_strncmp, compare_identical_strings)
{
    int result = my_strncmp("hello", "hello", 5);
    int expected = strncmp("hello", "hello", 5);
    cr_assert_eq(result, expected);
}

Test(my_strncmp, compare_different_strings)
{
    int result = my_strncmp("hello", "world", 5);
    int expected = strncmp("hello", "world", 5);
    cr_assert_eq(result, expected);
}

Test(my_strncmp, compare_zero_chars)
{
    int result = my_strncmp("hello", "world", 0);
    int expected = strncmp("hello", "world", 0);
    cr_assert_eq(result, expected);
}

Test(my_strncmp, compare_first_chars_only)
{
    int result = my_strncmp("abc", "abd", 2);
    int expected = strncmp("abc", "abd", 2);
    cr_assert_eq(result, expected);
}

Test(my_strncmp, compare_partial_match)
{
    int result = my_strncmp("hello", "help", 3);
    int expected = strncmp("hello", "help", 3);
    cr_assert_eq(result, expected);
}

Test(my_strncmp, compare_empty_strings)
{
    int result = my_strncmp("", "", 1);
    int expected = strncmp("", "", 1);
    cr_assert_eq(result, expected);
}

Test(my_strncmp, compare_one_empty_string)
{
    int result = my_strncmp("hello", "", 3);
    int expected = strncmp("hello", "", 3);
    cr_assert_eq(result, expected);
}

Test(my_strncmp, compare_longer_than_strings)
{
    int result = my_strncmp("hi", "hi", 10);
    int expected = strncmp("hi", "hi", 10);
    cr_assert_eq(result, expected);
}
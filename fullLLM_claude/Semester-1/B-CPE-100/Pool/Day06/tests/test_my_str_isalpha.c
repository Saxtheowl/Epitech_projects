/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** test_my_str_isalpha.c
*/

#include <criterion/criterion.h>

int my_str_isalpha(char const *str);

Test(my_str_isalpha, only_lowercase)
{
    int result = my_str_isalpha("hello");
    cr_assert_eq(result, 1);
}

Test(my_str_isalpha, only_uppercase)
{
    int result = my_str_isalpha("HELLO");
    cr_assert_eq(result, 1);
}

Test(my_str_isalpha, mixed_case)
{
    int result = my_str_isalpha("HeLLo");
    cr_assert_eq(result, 1);
}

Test(my_str_isalpha, empty_string)
{
    int result = my_str_isalpha("");
    cr_assert_eq(result, 1);
}

Test(my_str_isalpha, with_numbers)
{
    int result = my_str_isalpha("Hello123");
    cr_assert_eq(result, 0);
}

Test(my_str_isalpha, with_spaces)
{
    int result = my_str_isalpha("Hello World");
    cr_assert_eq(result, 0);
}

Test(my_str_isalpha, with_symbols)
{
    int result = my_str_isalpha("Hello!");
    cr_assert_eq(result, 0);
}
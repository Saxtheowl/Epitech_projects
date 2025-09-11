/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** test_my_str_islower.c
*/

#include <criterion/criterion.h>

int my_str_islower(char const *str);

Test(my_str_islower, only_lowercase)
{
    int result = my_str_islower("hello");
    cr_assert_eq(result, 1);
}

Test(my_str_islower, empty_string)
{
    int result = my_str_islower("");
    cr_assert_eq(result, 1);
}

Test(my_str_islower, with_uppercase)
{
    int result = my_str_islower("Hello");
    cr_assert_eq(result, 0);
}

Test(my_str_islower, with_numbers)
{
    int result = my_str_islower("hello123");
    cr_assert_eq(result, 0);
}

Test(my_str_islower, with_spaces)
{
    int result = my_str_islower("hello world");
    cr_assert_eq(result, 0);
}

Test(my_str_islower, single_char_lower)
{
    int result = my_str_islower("a");
    cr_assert_eq(result, 1);
}

Test(my_str_islower, single_char_upper)
{
    int result = my_str_islower("A");
    cr_assert_eq(result, 0);
}
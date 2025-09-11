/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** test_my_strncmp.c
*/

#include <criterion/criterion.h>
#include <string.h>

int my_strncmp(char const *s1, char const *s2, int n);

Test(my_strncmp, equal_strings)
{
    int result = my_strncmp("Hello", "Hello", 5);
    cr_assert_eq(result, 0);
}

Test(my_strncmp, different_strings)
{
    int result = my_strncmp("Hello", "World", 5);
    cr_assert_lt(result, 0);
}

Test(my_strncmp, compare_zero_chars)
{
    int result = my_strncmp("Hello", "World", 0);
    cr_assert_eq(result, 0);
}

Test(my_strncmp, partial_comparison)
{
    int result = my_strncmp("Hello", "Help", 3);
    cr_assert_eq(result, 0);
}

Test(my_strncmp, compare_with_stdlib)
{
    char *s1 = "Hello";
    char *s2 = "Help";
    int my_result = my_strncmp(s1, s2, 4);
    int stdlib_result = strncmp(s1, s2, 4);
    
    if (my_result < 0 && stdlib_result < 0)
        cr_assert(1);
    else if (my_result > 0 && stdlib_result > 0)
        cr_assert(1);
    else
        cr_assert_eq(my_result, stdlib_result);
}

Test(my_strncmp, first_shorter)
{
    int result = my_strncmp("Hi", "Hello", 5);
    cr_assert_lt(result, 0);
}
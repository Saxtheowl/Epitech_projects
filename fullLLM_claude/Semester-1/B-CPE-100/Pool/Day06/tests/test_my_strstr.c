/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** test_my_strstr.c
*/

#include <criterion/criterion.h>
#include <string.h>

char *my_strstr(char *str, char const *to_find);

Test(my_strstr, find_hello_in_hello_world)
{
    char str[] = "Hello World";
    char *result = my_strstr(str, "Hello");
    cr_assert_eq(result, str);
}

Test(my_strstr, find_world_in_hello_world)
{
    char str[] = "Hello World";
    char *result = my_strstr(str, "World");
    cr_assert_eq(result, str + 6);
}

Test(my_strstr, find_empty_string)
{
    char str[] = "Hello World";
    char *result = my_strstr(str, "");
    cr_assert_eq(result, str);
}

Test(my_strstr, not_found)
{
    char str[] = "Hello World";
    char *result = my_strstr(str, "xyz");
    cr_assert_eq(result, (char *)0);
}

Test(my_strstr, find_single_char)
{
    char str[] = "Hello World";
    char *result = my_strstr(str, "o");
    cr_assert_eq(result, str + 4);
}

Test(my_strstr, compare_with_stdlib)
{
    char str[] = "Hello World Test";
    char *my_result = my_strstr(str, "Test");
    char *stdlib_result = strstr(str, "Test");
    cr_assert_eq(my_result, stdlib_result);
}
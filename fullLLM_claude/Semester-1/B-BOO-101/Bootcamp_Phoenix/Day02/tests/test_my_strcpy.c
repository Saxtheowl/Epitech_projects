/*
** EPITECH PROJECT, 2024
** Day02 - Bootcamp Phoenix
** File description:
** Unit tests for my_strcpy function using Criterion
*/

#include <criterion/criterion.h>
#include <string.h>

char *my_strcpy(char *dest, char const *src);

Test(my_strcpy, copy_in_empty_array)
{
    char dest[6] = {0};
    my_strcpy(dest, "Hello");
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strcpy, copy_string_in_empty_array)
{
    char my_dest[6] = {0};
    char dest[6] = {0};
    my_strcpy(my_dest, "Hello");
    strcpy(dest, "Hello");
    cr_assert_str_eq(my_dest, dest);
}

Test(my_strcpy, copy_empty_string)
{
    char dest[10] = "previous";
    my_strcpy(dest, "");
    cr_assert_str_eq(dest, "");
}

Test(my_strcpy, copy_single_char)
{
    char dest[2] = {0};
    my_strcpy(dest, "A");
    cr_assert_str_eq(dest, "A");
}

Test(my_strcpy, copy_overwrites_previous_content)
{
    char dest[10] = "old";
    my_strcpy(dest, "new");
    cr_assert_str_eq(dest, "new");
}

Test(my_strcpy, copy_longer_string)
{
    char dest[20] = {0};
    char *src = "This is a test";
    my_strcpy(dest, src);
    cr_assert_str_eq(dest, src);
}
/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** test_my_str_isprintable.c
*/

#include <criterion/criterion.h>

int my_str_isprintable(char const *str);

Test(my_str_isprintable, normal_string)
{
    int result = my_str_isprintable("Hello World 123 !@#");
    cr_assert_eq(result, 1);
}

Test(my_str_isprintable, empty_string)
{
    int result = my_str_isprintable("");
    cr_assert_eq(result, 1);
}

Test(my_str_isprintable, with_newline)
{
    char str[] = {'H', 'e', 'l', 'l', 'o', '\n', '\0'};
    int result = my_str_isprintable(str);
    cr_assert_eq(result, 0);
}

Test(my_str_isprintable, with_tab)
{
    char str[] = {'H', 'e', 'l', 'l', 'o', '\t', '\0'};
    int result = my_str_isprintable(str);
    cr_assert_eq(result, 0);
}

Test(my_str_isprintable, all_printable_ascii)
{
    int result = my_str_isprintable(" !\"#$%&'()*+,-./0123456789:;<=>?@");
    cr_assert_eq(result, 1);
}

Test(my_str_isprintable, space_only)
{
    int result = my_str_isprintable("   ");
    cr_assert_eq(result, 1);
}

Test(my_str_isprintable, with_null_byte)
{
    char str[] = {'H', 'e', 'l', '\0', 'l', 'o', '\0'};
    int result = my_str_isprintable(str);
    cr_assert_eq(result, 1);
}
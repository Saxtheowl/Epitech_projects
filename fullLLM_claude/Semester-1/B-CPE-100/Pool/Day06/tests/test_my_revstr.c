/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** test_my_revstr.c
*/

#include <criterion/criterion.h>
#include <string.h>

char *my_revstr(char *str);

Test(my_revstr, reverse_hello)
{
    char str[] = "Hello";
    my_revstr(str);
    cr_assert_str_eq(str, "olleH");
}

Test(my_revstr, reverse_empty_string)
{
    char str[] = "";
    my_revstr(str);
    cr_assert_str_eq(str, "");
}

Test(my_revstr, reverse_single_char)
{
    char str[] = "A";
    my_revstr(str);
    cr_assert_str_eq(str, "A");
}

Test(my_revstr, reverse_two_chars)
{
    char str[] = "AB";
    my_revstr(str);
    cr_assert_str_eq(str, "BA");
}

Test(my_revstr, reverse_palindrome)
{
    char str[] = "ABBA";
    my_revstr(str);
    cr_assert_str_eq(str, "ABBA");
}

Test(my_revstr, reverse_long_string)
{
    char str[] = "EPITECH";
    my_revstr(str);
    cr_assert_str_eq(str, "HCETIPE");
}
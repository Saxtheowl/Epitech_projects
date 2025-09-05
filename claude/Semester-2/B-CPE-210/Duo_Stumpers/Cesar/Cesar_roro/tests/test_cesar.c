/*
** EPITECH PROJECT, 2025
** Cesar
** File description:
** test_cesar
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "cesar.h"

Test(cesar, caesar_encrypt_char_uppercase)
{
    cr_assert_eq(caesar_encrypt_char('A', 3), 'D');
    cr_assert_eq(caesar_encrypt_char('B', 3), 'E');
    cr_assert_eq(caesar_encrypt_char('Y', 1), 'Z');
}

Test(cesar, caesar_encrypt_char_lowercase)
{
    cr_assert_eq(caesar_encrypt_char('a', 3), 'd');
    cr_assert_eq(caesar_encrypt_char('b', 3), 'e');
    cr_assert_eq(caesar_encrypt_char('y', 1), 'z');
}

Test(cesar, caesar_encrypt_char_non_alpha)
{
    cr_assert_eq(caesar_encrypt_char('!', 3), '!');
    cr_assert_eq(caesar_encrypt_char(' ', 5), ' ');
    cr_assert_eq(caesar_encrypt_char('1', 2), '1');
}

Test(cesar, caesar_encrypt_char_negative_key)
{
    cr_assert_eq(caesar_encrypt_char('D', -3), 'A');
    cr_assert_eq(caesar_encrypt_char('d', -3), 'a');
}

Test(cesar, utils_my_strlen)
{
    cr_assert_eq(my_strlen("hello"), 5);
    cr_assert_eq(my_strlen(""), 0);
    cr_assert_eq(my_strlen(NULL), 0);
}

Test(cesar, utils_my_atoi)
{
    cr_assert_eq(my_atoi("123"), 123);
    cr_assert_eq(my_atoi("-5"), -5);
    cr_assert_eq(my_atoi("+10"), 10);
}
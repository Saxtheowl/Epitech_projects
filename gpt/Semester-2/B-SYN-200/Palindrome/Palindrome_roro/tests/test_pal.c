/*
** EPITECH PROJECT, 2025
** Palindrome
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "palindrome.h"

Test(pal, base10_reverse)
{
    cr_assert_eq(reverse_in_base(123, 10), 321);
}

Test(pal, palindrome_detect)
{
    cr_assert(is_palindrome_base(9339, 10));
}

Test(pal, reverse_in_base2)
{
    cr_assert_eq(reverse_in_base(0b101101, 2), 0b110101);
}

Test(pal, find_pal_basic)
{
    long res; int it;
    /* 87 becomes palindrome in base 10 after a few iterations */
    cr_assert(find_palindrome(87, 10, 100, &res, &it));
    cr_assert(is_palindrome_base(res, 10));
}

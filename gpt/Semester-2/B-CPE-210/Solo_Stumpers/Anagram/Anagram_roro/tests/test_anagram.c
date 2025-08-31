/*
** EPITECH PROJECT, 2025
** Anagram
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "anagram.h"

Test(anagram, basic)
{
    cr_assert(is_anagram("listen", "silent"));
    cr_assert(is_anagram("Debit Card", "Bad Credit"));
    cr_assert_not(is_anagram("abc", "ab"));
}

Test(anagram, punctuation_and_case)
{
    cr_assert(is_anagram("A gentleman", "Elegant man!"));
    cr_assert_not(is_anagram("Hello", "Ole!"));
}

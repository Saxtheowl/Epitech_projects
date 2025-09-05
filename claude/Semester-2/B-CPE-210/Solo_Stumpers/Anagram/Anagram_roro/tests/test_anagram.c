/*
** EPITECH PROJECT, 2025
** Anagram
** File description:
** Unit tests for anagram
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "anagram.h"

Test(anagram, test_valid_anagrams)
{
    cr_redirect_stdout();
    anagram_check("Rail Safety", "Fairy tales");
    cr_assert_stdout_eq_str("anagram!\n");
}

Test(anagram, test_invalid_anagrams)
{
    cr_redirect_stdout();
    anagram_check("moo", "moon");
    cr_assert_stdout_eq_str("no anagrams.\n");
}

Test(anagram, test_case_insensitive)
{
    cr_redirect_stdout();
    anagram_check("Listen", "Silent");
    cr_assert_stdout_eq_str("anagram!\n");
}

Test(anagram, test_empty_strings)
{
    cr_redirect_stdout();
    anagram_check("", "");
    cr_assert_stdout_eq_str("anagram!\n");
}

Test(anagram, test_single_char)
{
    cr_redirect_stdout();
    anagram_check("a", "a");
    cr_assert_stdout_eq_str("anagram!\n");
}

Test(anagram, test_different_lengths)
{
    cr_redirect_stdout();
    anagram_check("abc", "abcd");
    cr_assert_stdout_eq_str("no anagrams.\n");
}
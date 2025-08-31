/*
** EPITECH PROJECT, 2025
** SortWords
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include <string.h>
#include "sort_words.h"

Test(sort_words, basic)
{
    char words[4][64] = {"banana", "apple", "pear", "apricot"};

    sort_words(words, 4);
    cr_assert_str_eq(words[0], "apple");
    cr_assert_str_eq(words[1], "apricot");
    cr_assert_str_eq(words[2], "banana");
    cr_assert_str_eq(words[3], "pear");
}

Test(split_words, whitespace_and_limits)
{
    char words[8][64];
    int n = split_words("  foo\tbar  baz\nqux  ", words, 8);
    cr_assert_eq(n, 4);
    cr_assert_str_eq(words[0], "foo");
    cr_assert_str_eq(words[1], "bar");
    cr_assert_str_eq(words[2], "baz");
    cr_assert_str_eq(words[3], "qux");
}

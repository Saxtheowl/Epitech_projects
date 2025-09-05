/*
** EPITECH PROJECT, 2025
** SortWords
** File description:
** Unit tests for sort_words
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "sort_words.h"

Test(sort_words, test_basic_sorting)
{
    cr_redirect_stdout();
    sort_words("somewhere i lost just my sanity");
    cr_assert_stdout_eq_str("i just lost my sanity somewhere\n");
}

Test(sort_words, test_case_insensitive)
{
    cr_redirect_stdout();
    sort_words("A a b B cc ca cd");
    cr_assert_stdout_eq_str("A a b B ca cc cd\n");
}

Test(sort_words, test_tabs)
{
    cr_redirect_stdout();
    sort_words("you\t\tlost");
    cr_assert_stdout_eq_str("lost you\n");
}

Test(sort_words, test_empty_string)
{
    cr_redirect_stdout();
    sort_words("");
    cr_assert_stdout_eq_str("\n");
}

Test(sort_words, test_single_word)
{
    cr_redirect_stdout();
    sort_words("hello");
    cr_assert_stdout_eq_str("hello\n");
}

Test(sort_words, test_multiple_spaces)
{
    cr_redirect_stdout();
    sort_words("  hello    world  ");
    cr_assert_stdout_eq_str("hello world\n");
}
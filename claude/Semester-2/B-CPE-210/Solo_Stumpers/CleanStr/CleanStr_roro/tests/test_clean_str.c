/*
** EPITECH PROJECT, 2025
** CleanStr
** File description:
** Unit tests for clean_str
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "clean_str.h"

Test(clean_str, test_basic_string)
{
    cr_redirect_stdout();
    clean_str("abc cba abc cab cba");
    cr_assert_stdout_eq_str("abc cba abc cab cba\n");
}

Test(clean_str, test_leading_trailing_spaces)
{
    cr_redirect_stdout();
    clean_str(" Remus and Romulus are the two mammals of Rome ");
    cr_assert_stdout_eq_str("Remus and Romulus are the two mammals of Rome\n");
}

Test(clean_str, test_tabs)
{
    cr_redirect_stdout();
    clean_str("\tHello\t\t how are you?\t ");
    cr_assert_stdout_eq_str("Hello how are you?\n");
}

Test(clean_str, test_empty_string)
{
    cr_redirect_stdout();
    clean_str("");
    cr_assert_stdout_eq_str("\n");
}

Test(clean_str, test_only_spaces)
{
    cr_redirect_stdout();
    clean_str("   ");
    cr_assert_stdout_eq_str("\n");
}

Test(clean_str, test_single_word)
{
    cr_redirect_stdout();
    clean_str("hello");
    cr_assert_stdout_eq_str("hello\n");
}
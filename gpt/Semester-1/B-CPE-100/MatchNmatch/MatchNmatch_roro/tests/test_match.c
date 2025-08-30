/*
** EPITECH PROJECT, 2025
** MatchNmatch_roro
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "matchnmatch.h"

Test(match, simple)
{
    cr_assert_eq(match("abc", "abc"), 1);
    cr_assert_eq(match("abc", "ab"), 0);
    cr_assert_eq(match("", ""), 1);
}

Test(match, star)
{
    cr_assert_eq(match("abc", "*"), 1);
    cr_assert_eq(match("abc", "a*c"), 1);
    cr_assert_eq(match("abc", "a*d"), 0);
    cr_assert_eq(match("", "*a"), 0);
}

Test(nmatch, paths)
{
    cr_assert_eq(nmatch("abc", "*"), 1);
    cr_assert_eq(nmatch("abbbc", "ab*c"), 1);
    cr_assert_eq(nmatch("", "*"), 1);
    cr_assert_eq(nmatch("abc", "a*b*c"), 1);
    cr_assert_eq(nmatch("aaa", "a*a"), 2);
}

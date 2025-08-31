/*
** EPITECH PROJECT, 2025
** CleanStr
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "clean_str.h"

Test(clean, trimming_and_spaces)
{
    char out[256];

    clean_string("  Hello,\tWorld!! ", out, 256);
    cr_assert_str_eq(out, "hello world");
}

Test(clean, alnum_and_separators)
{
    char out[256];
    clean_string("foo_bar-123", out, 256);
    cr_assert_str_eq(out, "foo bar 123");
}

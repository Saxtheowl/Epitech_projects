/*
** EPITECH PROJECT, 2025
** GeekNameFormatter
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "geek_name.h"

Test(geek, mapping)
{
    char out[128];

    geekify("Testing is awesome", out, 128);
    cr_assert_str_eq(out, "7es7ing 1s awes0me");
}

Test(geek, preserves_other_chars)
{
    char out[128];

    geekify("123_ABC", out, 128);
    cr_assert_str_eq(out, "123_4BC");
}

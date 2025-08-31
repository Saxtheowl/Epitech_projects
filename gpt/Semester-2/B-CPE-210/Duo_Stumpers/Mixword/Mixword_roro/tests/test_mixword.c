/*
** EPITECH PROJECT, 2025
** Mixword
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "mixword.h"

Test(mixword, basic)
{
    char out[128];

    mixword("abc", "XYZ", out, 128);
    cr_assert_str_eq(out, "aXbYcZ");
}

Test(mixword, uneven)
{
    char out[128];

    mixword("ab", "WXYZ", out, 128);
    cr_assert_str_eq(out, "aWbXYZ");
}


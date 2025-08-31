/*
** EPITECH PROJECT, 2025
** Cesar
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "cesar.h"

Test(cesar, shift_basic)
{
    char out[128];

    cesar_cipher("Abc Z", out, 128, 2);
    cr_assert_str_eq(out, "Cde B");
}

Test(cesar, negative_shift)
{
    char out[128];

    cesar_cipher("Bcd", out, 128, -1);
    cr_assert_str_eq(out, "Abc");
}

Test(cesar, wrap_around)
{
    char out[128];

    cesar_cipher("Zz", out, 128, 2);
    cr_assert_str_eq(out, "Bb");
}

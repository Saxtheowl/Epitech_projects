/*
** EPITECH PROJECT, 2025
** TextToMultiTap
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "multitap.h"

Test(multitap, hello_world)
{
    char out[256];

    text_to_multitap("Hello World", out, 256);
    cr_assert_str_eq(out, "4433555 5556660 96667775553");
}

Test(multitap, adjacent_keys_spacing)
{
    char out[256];

    text_to_multitap("ad", out, 256); /* a->2, d->3 (no space) */
    cr_assert_str_eq(out, "23");

    text_to_multitap("aa", out, 256); /* same key: needs space */
    cr_assert_str_eq(out, "2 2");
}

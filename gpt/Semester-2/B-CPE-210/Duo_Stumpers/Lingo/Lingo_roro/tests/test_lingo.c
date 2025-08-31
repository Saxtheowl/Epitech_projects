/*
** EPITECH PROJECT, 2025
** Lingo
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "lingo.h"

Test(lingo, basic_hint)
{
    char out[64];

    lingo_hint("apple", "allee", out, 64);
    cr_assert_str_eq(out, "Al.e.");
}

Test(lingo, duplicate_letters_handling)
{
    char out[64];
    /* target has one 'l'; guess has two: only one should be marked */
    lingo_hint("mole", "ball", out, 64);
    /* b(.), a(.), l(lowercase present), l(.) */
    cr_assert_str_eq(out, "..l.");
}

Test(lingo, all_correct)
{
    char out[64];
    lingo_hint("crate", "CrAtE", out, 64);
    cr_assert_str_eq(out, "CRATE");
}

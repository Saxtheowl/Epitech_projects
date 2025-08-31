/*
** EPITECH PROJECT, 2025
** USNameFormatter
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "us_name.h"

Test(us_name, simple)
{
    char out[256];

    format_name_us("john DOE", out, 256);
    cr_assert_str_eq(out, "DOE, John");
}

Test(us_name, middle_name)
{
    char out[256];

    format_name_us("john ronald reuel TOLKIEN", out, 256);
    cr_assert_str_eq(out, "TOLKIEN, John Ronald Reuel");
}

Test(us_name, extra_spaces_and_case)
{
    char out[256];
    format_name_us("  aLiCe   bOb  ", out, 256);
    cr_assert_str_eq(out, "BOB, Alice");
}

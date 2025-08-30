/*
** EPITECH PROJECT, 2025
** MyLs_roro
** File description:
** Tests for flag parsing
*/

#include <criterion/criterion.h>
#include "my_ls.h"

Test(parse_flags, combos)
{
    flags_t f;
    int idx = 0;
    char *av[] = {"my_ls", "-alRt", "--", "/"};
    int ac = 4;

    cr_assert_eq(parse_flags(ac, av, &idx, &f), 0);
    cr_assert(f.a && f.l && f.R && f.t);
    cr_assert_eq(idx, 2);
}

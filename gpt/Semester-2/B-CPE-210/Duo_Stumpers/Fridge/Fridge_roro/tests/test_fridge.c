/*
** EPITECH PROJECT, 2025
** Fridge
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "fridge.h"

Test(fridge, parse_and_check)
{
    item_t inv[8];
    item_t rec[8];
    int ni = parse_list("milk:2, sugar:1", inv, 8);
    int nr = parse_list("milk:1, sugar:2", rec, 8);

    cr_assert_eq(ni, 2);
    cr_assert_eq(nr, 2);
    cr_assert_not(can_prepare(inv, ni, rec, nr));
}


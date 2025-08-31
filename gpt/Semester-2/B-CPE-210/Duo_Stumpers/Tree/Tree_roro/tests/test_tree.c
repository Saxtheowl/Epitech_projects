/*
** EPITECH PROJECT, 2025
** Tree
** File description:
** Tests (logic helpers)
*/

#include <criterion/criterion.h>
#include "tree.h"

Test(tree, parse)
{
    int n;

    cr_assert(parse_positive_int("5", &n));
    cr_assert_eq(n, 5);
    cr_assert_not(parse_positive_int("0", &n));
}


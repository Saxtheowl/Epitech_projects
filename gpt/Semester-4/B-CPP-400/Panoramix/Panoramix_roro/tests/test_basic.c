/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
**   Minimal test
*/

#include <criterion/criterion.h>
#include "panoramix.h"

Test(args, atoi)
{
    int v = -1;
    cr_assert_eq(my_atoi_strict("123", &v), 0);
    cr_assert_eq(v, 123);
}


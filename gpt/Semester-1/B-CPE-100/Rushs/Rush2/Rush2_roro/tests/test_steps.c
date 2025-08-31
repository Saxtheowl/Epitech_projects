/*
** EPITECH PROJECT, 2025
** Rush2_roro
** File description:
** Basic tests
*/

#include <criterion/criterion.h>
#include "rush2.h"

Test(step02, good)
{
    cr_assert_eq(step02_main("qwertyuiopasdfghjklzxcvbnm"), 0);
    cr_assert_eq(step02_main("abcdefghijklmnopqrstuvwxyz"), 0);
}

Test(step02, bad)
{
    cr_assert_eq(step02_main("abc"), ERR_CODE);
}

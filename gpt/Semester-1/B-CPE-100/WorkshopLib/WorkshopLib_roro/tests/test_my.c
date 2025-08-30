/*
** EPITECH PROJECT, 2025
** WorkshopLib_roro
** File description:
** Tests for libmy
*/

#include <criterion/criterion.h>
#include "my.h"

Test(my_strlen, basics)
{
    cr_assert_eq(my_strlen("hello"), 5);
    cr_assert_eq(my_strlen(""), 0);
}

Test(my_strcmp, order)
{
    cr_assert(my_strcmp("abc", "abc") == 0);
    cr_assert(my_strcmp("abc", "abd") < 0);
    cr_assert(my_strcmp("abe", "abd") > 0);
}

/*
** EPITECH PROJECT, 2025
** Day03_roro
** File description:
** test_my_strlen
*/

#include <criterion/criterion.h>
#include "my.h"

Test(my_strlen, simple_string)
{
    cr_assert_eq(my_strlen("Hello World!"), 12);
}

Test(my_strlen, empty_string)
{
    cr_assert_eq(my_strlen(""), 0);
}

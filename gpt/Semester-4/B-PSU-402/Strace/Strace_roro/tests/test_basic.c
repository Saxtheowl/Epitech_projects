/*
** EPITECH PROJECT, 2025
** strace tests
** File description:
**   Basic Criterion test
*/

#include <criterion/criterion.h>

Test(basic, always_true)
{
    cr_assert(1);
}


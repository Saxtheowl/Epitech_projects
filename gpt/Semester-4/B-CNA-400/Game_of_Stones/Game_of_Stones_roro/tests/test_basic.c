/*
** EPITECH PROJECT, 2025
** Game_of_Stones
** File description:
**   Minimal Criterion tests
*/

#include <criterion/criterion.h>
#include "gos.h"

Test(strings, len)
{
    cr_assert_eq(gos_strlen("abc"), 3);
}


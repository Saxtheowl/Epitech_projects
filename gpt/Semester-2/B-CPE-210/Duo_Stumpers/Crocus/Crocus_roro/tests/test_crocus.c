/*
** EPITECH PROJECT, 2025
** Crocus
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "crocus.h"

Test(crocus, rotations)
{
    cr_assert(is_rotation("abcde", "cdeab"));
    cr_assert_not(is_rotation("abc", "acb"));
}


/*
** EPITECH PROJECT, 2025
** SpongeBobCaseChecker
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "spongebob.h"

Test(spongebob, alternating)
{
    cr_assert(is_spongebob_case("hElLo"));
    cr_assert(is_spongebob_case("HeLlO"));
    cr_assert_not(is_spongebob_case("Hello"));
}

Test(spongebob, ignore_non_letters)
{
    cr_assert(is_spongebob_case("h-E_l+L=o"));
    cr_assert_not(is_spongebob_case("hE__LL__o"));
}

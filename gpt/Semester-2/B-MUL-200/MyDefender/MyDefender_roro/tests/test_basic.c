/*
** EPITECH PROJECT, 2025
** MyDefender
** File description:
** Basic test
*/

#include <criterion/criterion.h>
#include "app.h"

Test(mydefender, run_app_returns_zero)
{
    cr_assert_eq(run_app(), 0);
}


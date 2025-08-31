/*
** EPITECH PROJECT, 2025
** MyRPG
** File description:
** Basic test
*/

#include <criterion/criterion.h>
#include "app.h"

Test(myrpg, run_app)
{
    cr_assert_eq(run_app(), 0);
}


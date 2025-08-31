/*
** EPITECH PROJECT, 2025
** My_paint
** File description:
** Basic test
*/

#include <criterion/criterion.h>
#include "app.h"

Test(mypaint, run_app)
{
    cr_assert_eq(run_app(), 0);
}


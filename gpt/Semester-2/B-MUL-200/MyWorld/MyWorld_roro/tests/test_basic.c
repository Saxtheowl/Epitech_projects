/*
** EPITECH PROJECT, 2025
** MyWorld
** File description:
** Basic test
*/

#include <criterion/criterion.h>
#include "app.h"

Test(myworld, run_app)
{
    cr_assert_eq(run_app(), 0);
}


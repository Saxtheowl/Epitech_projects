/*
** EPITECH PROJECT, 2025
** Panoramix_roro
** File description:
** test_basic.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "panoramix.h"

Test(panoramix, runs_and_returns_zero)
{
    int rc;

    cr_redirect_stdout();
    cr_redirect_stderr();
    rc = run_panoramix(3, 2, 2, 1);
    cr_assert_eq(rc, 0);
}


/*
** EPITECH PROJECT, 2025
** mini_printf_roro
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "mini_printf.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
}

Test(mini, basics, .init = redirect_all_stdout)
{
    mini_printf("A %s %d %i %c %%", "x", -3, 7, 'Z');
    cr_assert_stdout_eq_str("A x -3 7 Z %");
}

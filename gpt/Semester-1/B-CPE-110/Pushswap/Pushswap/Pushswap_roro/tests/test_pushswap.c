/*
** EPITECH PROJECT, 2025
** Pushswap_roro
** File description:
** Basic tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "pushswap.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
}

Test(pushswap, small, .init = redirect_all_stdout)
{
    char *av[] = {"pushswap", "3", "2", "1"};
    int ac = 4;
    cr_assert_eq(run_pushswap(ac, av), 0);
}

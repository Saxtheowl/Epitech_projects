/*
** EPITECH PROJECT, 2025
** Star_roro
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "star.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
}

Test(star, size1, .init = redirect_all_stdout)
{
    print_star(1);
    fflush(stdout);
    cr_assert_stdout_eq_str(
        "   *\n*** ***\n *   *\n*** ***\n   *\n");
}

Test(star, size2, .init = redirect_all_stdout)
{
    print_star(2);
    fflush(stdout);
    cr_assert_stdout_eq_str(
        "     *\n"
        "    * *\n"
        "***** *****\n"
        " *       *\n"
        "  *     *\n"
        " *       *\n"
        "***** *****\n"
        "    * *\n"
        "     *\n");
}

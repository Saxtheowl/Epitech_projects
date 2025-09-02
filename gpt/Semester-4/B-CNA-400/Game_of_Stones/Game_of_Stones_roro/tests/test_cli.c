/*
** EPITECH PROJECT, 2025
** Game_of_Stones
** File description:
**   CLI integration tests with stdout capture
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <string.h>
#include "gos.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(links_mode, jon_to_cersei, .init = redirect_all_stdout)
{
    int st = run_links_mode("tests/resources/friends.txt", "Jon Snow", "Cersei Lannister");
    fflush(stdout);
    cr_assert_eq(st, 0);
    cr_assert(strstr(cr_get_redirected_stdout(), "Degree of separation") != NULL);
}

Test(plots_mode, safe_result, .init = redirect_all_stdout)
{
    int st = run_plots_mode("tests/resources/friends.txt", "tests/resources/plots.txt", 3);
    fflush(stdout);
    cr_assert_eq(st, 0);
    cr_assert(strstr(cr_get_redirected_stdout(), "The stone is safe!") != NULL);
}

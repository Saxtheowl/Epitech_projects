/*
** EPITECH PROJECT, 2025
** Panoramix_bootstrap tests
** File description:
**   Basic tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
int panoramix_bootstrap_main(int ac, char **av);

static void redirect_all(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(help_flag, prints_usage, .init = redirect_all)
{
    char *argv[] = {"./panoramix_bootstrap", "-h", NULL};
    int ret = panoramix_bootstrap_main(2, argv);
    cr_assert_eq(ret, 0);
    cr_assert(strstr(cr_get_redirected_stdout(), "Simulates") != NULL);
}


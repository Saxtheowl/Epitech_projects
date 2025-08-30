/*
** EPITECH PROJECT, 2025
** Tree_roro
** File description:
** Basic test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "tree.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
}

Test(tree, size0, .init = redirect_all_stdout)
{
    print_tree(0);
    cr_assert_stdout_eq_str("");
}

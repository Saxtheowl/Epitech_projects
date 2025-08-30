/*
** EPITECH PROJECT, 2025
** Day02_roro
** File description:
** test_my_put_nbr
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_put_nbr, simple_number, .init = redirect_all_std)
{
    my_put_nbr(42);
    cr_assert_stdout_eq_str("42");
}

Test(my_put_nbr, negative_number, .init = redirect_all_std)
{
    my_put_nbr(-42);
    cr_assert_stdout_eq_str("-42");
}

Test(my_put_nbr, zero, .init = redirect_all_std)
{
    my_put_nbr(0);
    cr_assert_stdout_eq_str("0");
}

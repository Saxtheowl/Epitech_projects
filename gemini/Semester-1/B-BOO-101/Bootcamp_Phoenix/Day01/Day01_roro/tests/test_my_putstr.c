/*
** EPITECH PROJECT, 2025
** Day01_roro
** File description:
** test_my_putstr
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_putstr, simple_string, .init = redirect_all_std)
{
    my_putstr("Hello World!");
    cr_assert_stdout_eq_str("Hello World!");
}

/*
** EPITECH PROJECT, 2025
** my_printf_roro
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my_printf.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
}

Test(my_printf, basics, .init = redirect_all_stdout)
{
    my_printf("Hello %s %d %x %%!", "X", 255, 255);
    cr_assert_stdout_eq_str("Hello X 255 ff %!");
}

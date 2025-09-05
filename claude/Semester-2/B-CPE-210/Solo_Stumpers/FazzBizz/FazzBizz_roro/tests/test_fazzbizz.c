/*
** EPITECH PROJECT, 2025
** FazzBizz
** File description:
** Unit tests for fazzbizz
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "fazzbizz.h"

Test(fazzbizz, test_basic_range)
{
    cr_redirect_stdout();
    fazzbizz(8, 12);
    cr_assert_stdout_eq_str("8\nBizz\nFazz\n11\n12\n");
}

Test(fazzbizz, test_fazzbizz_case)
{
    cr_redirect_stdout();
    fazzbizz(89, 91);
    cr_assert_stdout_eq_str("89\nFazzBizz\n91\n");
}

Test(fazzbizz, test_single_number)
{
    cr_redirect_stdout();
    fazzbizz(90, 90);
    cr_assert_stdout_eq_str("FazzBizz\n");
}

Test(fazzbizz, test_fazz_only)
{
    cr_redirect_stdout();
    fazzbizz(10, 10);
    cr_assert_stdout_eq_str("Fazz\n");
}

Test(fazzbizz, test_bizz_only)
{
    cr_redirect_stdout();
    fazzbizz(9, 9);
    cr_assert_stdout_eq_str("Bizz\n");
}

Test(fazzbizz, test_normal_numbers)
{
    cr_redirect_stdout();
    fazzbizz(1, 3);
    cr_assert_stdout_eq_str("1\n2\n3\n");
}
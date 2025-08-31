/*
** EPITECH PROJECT, 2025
** FazzBizz
** File description:
** Basic unit tests
*/

#include <criterion/criterion.h>
#include "fazzbizz.h"

Test(fazzbizz, multiples)
{
    cr_assert(is_multiple(6, 3));
    cr_assert_not(is_multiple(7, 3));
}

Test(parse, ok_and_fail)
{
    int n;

    cr_assert(parse_positive_int("15", &n));
    cr_assert_eq(n, 15);
    cr_assert_not(parse_positive_int("-1", &n));
    cr_assert_not(parse_positive_int("abc", &n));
}

Test(parse, bounds)
{
    int n;
    cr_assert_not(parse_positive_int("0", &n));
    cr_assert_not(parse_positive_int("1000000000000", &n));
}

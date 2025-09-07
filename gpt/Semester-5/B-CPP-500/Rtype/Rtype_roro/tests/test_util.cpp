/*
** EPITECH PROJECT, 2025
** Rtype_roro tests
** File description:
**   util tests
*/

#include <criterion/criterion.h>
#include "util.hpp"

Test(util, parse_port_ok)
{
    int p;
    cr_assert(parse_port("1234", p));
    cr_assert_eq(p, 1234);
}

Test(util, parse_port_bad)
{
    int p;
    cr_assert(!parse_port("abc", p));
    cr_assert(!parse_port("70000", p));
}


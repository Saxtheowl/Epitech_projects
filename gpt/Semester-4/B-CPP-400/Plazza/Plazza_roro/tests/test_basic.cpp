/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
**   Minimal test
*/

#include <criterion/criterion.h>
#include "plazza.hpp"

Test(parse, ok)
{
    auto o = parse_order_line("margarita S x2; regina XL x1");
    cr_assert(o.has_value());
}


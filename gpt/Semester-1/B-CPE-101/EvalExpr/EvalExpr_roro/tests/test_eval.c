/*
** EPITECH PROJECT, 2025
** EvalExpr_roro
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "eval.h"

Test(eval, basics)
{
    int ok = 0;
    cr_assert_eq(eval_expr("1+2*3", &ok), 7);
    cr_assert(ok);
}

Test(eval, paren)
{
    int ok = 0;
    cr_assert_eq(eval_expr("(1+2)*3", &ok), 9);
    cr_assert(ok);
}

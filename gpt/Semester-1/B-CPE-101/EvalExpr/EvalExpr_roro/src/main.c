/*
** EPITECH PROJECT, 2025
** EvalExpr_roro
** File description:
** Main
*/

#include <stdio.h>
#include "eval.h"

int main(int ac, char **av)
{
    int ok;
    long v;

    if (ac != 2)
        return ERR_CODE;
    v = eval_expr(av[1], &ok);
    if (!ok)
        return ERR_CODE;
    printf("%ld\n", v);
    return 0;
}

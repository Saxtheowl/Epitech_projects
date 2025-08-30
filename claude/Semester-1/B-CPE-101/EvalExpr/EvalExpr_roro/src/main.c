/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** main function for eval_expr
*/

#include "../include/eval_expr.h"
#include "../include/my.h"

int main(int ac, char **av)
{
    if (ac == 2) {
        my_put_nbr(eval_expr(av[1]));
        my_putchar('\n');
        return 0;
    }
    return 84;
}
/*
** EPITECH PROJECT, 2024
** Day10 - operations
** File description:
** Operation functions for advanced do_op - Task 05
*/

#include "include/my.h"

int my_add(int a, int b)
{
    return (a + b);
}

int my_sub(int a, int b)
{
    return (a - b);
}

int my_div(int a, int b)
{
    if (b == 0) {
        my_putstr("Stop: division by zero\n");
        return (0);
    }
    return (a / b);
}

int my_mul(int a, int b)
{
    return (a * b);
}

int my_mod(int a, int b)
{
    if (b == 0) {
        my_putstr("Stop: modulo by zero\n");
        return (0);
    }
    return (a % b);
}

int my_usage(int a, int b)
{
    (void)a;
    (void)b;
    my_putstr("0\n");
    return (0);
}
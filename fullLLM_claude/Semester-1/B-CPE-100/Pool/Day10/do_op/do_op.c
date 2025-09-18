/*
** EPITECH PROJECT, 2024
** Day10 - do_op
** File description:
** Simple calculator - Task 02
*/

#include <unistd.h>
#include "../include/my.h"

int my_addition(int a, int b)
{
    return (a + b);
}

int my_subtraction(int a, int b)
{
    return (a - b);
}

int my_multiplication(int a, int b)
{
    return (a * b);
}

int my_division(int a, int b)
{
    if (b == 0) {
        my_putstr("Stop: division by zero\n");
        return (0);
    }
    return (a / b);
}

int my_modulo(int a, int b)
{
    if (b == 0) {
        my_putstr("Stop: modulo by zero\n");
        return (0);
    }
    return (a % b);
}

int calculate(int a, char op, int b)
{
    if (op == '+')
        return (my_addition(a, b));
    if (op == '-')
        return (my_subtraction(a, b));
    if (op == '*')
        return (my_multiplication(a, b));
    if (op == '/')
        return (my_division(a, b));
    if (op == '%')
        return (my_modulo(a, b));
    my_putstr("0\n");
    return (0);
}

int main(int argc, char **argv)
{
    int a;
    int b;
    int result;

    if (argc != 4) {
        my_putstr("0\n");
        return (0);
    }
    
    if (my_strlen(argv[2]) != 1) {
        my_putstr("0\n");
        return (0);
    }

    a = my_getnbr(argv[1]);
    b = my_getnbr(argv[3]);
    
    if (argv[2][0] == '/' && b == 0) {
        my_putstr("Stop: division by zero\n");
        return (0);
    }
    
    if (argv[2][0] == '%' && b == 0) {
        my_putstr("Stop: modulo by zero\n");
        return (0);
    }
    
    result = calculate(a, argv[2][0], b);
    my_putnbr(result);
    my_putchar('\n');
    return (0);
}
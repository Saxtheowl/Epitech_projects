/*
** EPITECH PROJECT, 2024
** Day10 - my_advanced_do_op
** File description:
** Advanced calculator using function pointers - Task 05
*/

#include "include/my.h"
#include "include/my_opp.h"

int find_operator(char *op)
{
    int i = 0;

    while (OPERATORS_FUNCS[i].op[0] != '\0') {
        if (my_strcmp(OPERATORS_FUNCS[i].op, op) == 0)
            return (i);
        i++;
    }
    return (5);
}

int main(int argc, char **argv)
{
    int a;
    int b;
    int result;
    int op_index;

    if (argc != 4) {
        my_usage(0, 0);
        return (0);
    }
    
    if (my_strlen(argv[2]) != 1) {
        my_usage(0, 0);
        return (0);
    }

    op_index = find_operator(argv[2]);
    a = my_getnbr(argv[1]);
    b = my_getnbr(argv[3]);
    
    if ((argv[2][0] == '/' || argv[2][0] == '%') && b == 0) {
        result = (*OPERATORS_FUNCS[op_index].func)(a, b);
        return (0);
    }
    
    result = (*OPERATORS_FUNCS[op_index].func)(a, b);
    
    if (op_index == 5) {
        return (0);
    }
    
    my_putnbr(result);
    my_putchar('\n');
    return (0);
}
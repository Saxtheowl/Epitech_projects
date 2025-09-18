/*
** EPITECH PROJECT, 2024
** Day10 - my_opp.h
** File description:
** Header for advanced do_op with function pointers - Task 05
*/

#ifndef MY_OPP_H_
#define MY_OPP_H_

struct operator {
    char *op;
    int (*func)(int, int);
};

int my_add(int a, int b);
int my_sub(int a, int b);
int my_div(int a, int b);
int my_mul(int a, int b);
int my_mod(int a, int b);
int my_usage(int a, int b);

const struct operator OPERATORS_FUNCS[] = {
    {"+", &my_add},
    {"-", &my_sub},
    {"/", &my_div},
    {"*", &my_mul},
    {"%", &my_mod},
    {"", &my_usage}
};

#endif
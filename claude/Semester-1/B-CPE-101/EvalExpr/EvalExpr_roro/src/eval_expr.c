/*
** EPITECH PROJECT, 2024
** eval_expr.c
** File description:
** arithmetic expression evaluator
*/

#include <stddef.h>
#include "../include/eval_expr.h"

static char *skip_whitespace(char const *str)
{
    while (*str == ' ' || *str == '\t')
        str++;
    return (char *)str;
}

static int parse_number(char const **str)
{
    int result = 0;
    int sign = 1;
    char const *s = *str;

    s = skip_whitespace(s);
    if (*s == '-') {
        sign = -1;
        s++;
    } else if (*s == '+') {
        s++;
    }
    while (*s >= '0' && *s <= '9') {
        result = result * 10 + (*s - '0');
        s++;
    }
    *str = s;
    return result * sign;
}

static int parse_expression(char const **str);

static int parse_factor(char const **str)
{
    char const *s = *str;
    int result = 0;

    s = skip_whitespace(s);
    if (*s == '(') {
        s++;
        result = parse_expression(&s);
        s = skip_whitespace(s);
        if (*s == ')')
            s++;
        *str = s;
        return result;
    }
    return parse_number(str);
}

static int parse_term(char const **str)
{
    int left = parse_factor(str);
    char const *s = *str;
    int right = 0;

    s = skip_whitespace(s);
    while (*s == '*' || *s == '/' || *s == '%') {
        char op = *s;
        
        s++;
        right = parse_factor(&s);
        if (op == '*')
            left = left * right;
        else if (op == '/')
            left = left / right;
        else if (op == '%')
            left = left % right;
        s = skip_whitespace(s);
    }
    *str = s;
    return left;
}

static int parse_expression(char const **str)
{
    int left = parse_term(str);
    char const *s = *str;
    int right = 0;

    s = skip_whitespace(s);
    while (*s == '+' || *s == '-') {
        char op = *s;
        
        s++;
        right = parse_term(&s);
        if (op == '+')
            left = left + right;
        else if (op == '-')
            left = left - right;
        s = skip_whitespace(s);
    }
    *str = s;
    return left;
}

int eval_expr(char const *str)
{
    if (str == NULL)
        return 0;
    return parse_expression(&str);
}
/*
** EPITECH PROJECT, 2024
** eval_expr.c
** File description:
** expression evaluator for bistromatic
*/

#include <stdlib.h>
#include "../include/bistromatic.h"

static char const *skip_spaces(char const *expr)
{
    while (*expr == ' ' || *expr == '\t')
        expr++;
    return expr;
}

static int is_operator(char const *ops, char c, int op_idx)
{
    return (ops[op_idx] == c);
}

static char *parse_number(char const *base, char const **expr)
{
    char const *start = *expr;
    char *num;
    int len = 0;
    int i = 0;
    int value = 0;
    int base_len = my_strlen(base);
    char *result;

    while (get_digit_value(base, start[len]) != -1)
        len++;
    if (len == 0)
        return NULL;
    num = malloc(len + 1);
    if (num == NULL)
        return NULL;
    while (i < len) {
        num[i] = start[i];
        i++;
    }
    num[i] = '\0';
    i = 0;
    while (num[i]) {
        value = value * base_len + get_digit_value(base, num[i]);
        i++;
    }
    result = malloc(20);
    if (result == NULL) {
        free(num);
        return NULL;
    }
    if (value == 0) {
        my_strcpy(result, "0");
    } else {
        int temp = value;
        int digits = 0;
        while (temp > 0) {
            result[digits] = (temp % 10) + '0';
            temp /= 10;
            digits++;
        }
        result[digits] = '\0';
        for (i = 0; i < digits / 2; i++) {
            char t = result[i];
            result[i] = result[digits - 1 - i];
            result[digits - 1 - i] = t;
        }
    }
    *expr = start + len;
    free(num);
    return result;
}

static char *parse_expression(char const *base, char const *ops,
    char const **expr);
static char *parse_term(char const *base, char const *ops,
    char const **expr);

static char *parse_factor(char const *base, char const *ops,
    char const **expr)
{
    char const *s = *expr;
    char *result = NULL;

    s = skip_spaces(s);
    if (is_operator(ops, *s, OP_OPEN_PARENT_IDX)) {
        s++;
        result = parse_expression(base, ops, &s);
        s = skip_spaces(s);
        if (is_operator(ops, *s, OP_CLOSE_PARENT_IDX))
            s++;
        *expr = s;
        return result;
    }
    if (is_operator(ops, *s, OP_SUB_IDX)) {
        s++;
        result = parse_factor(base, ops, &s);
        if (result && result[0] == '-') {
            char *temp = my_strdup(result + 1);
            free(result);
            result = temp;
        } else if (result) {
            char *temp = malloc(my_strlen(result) + 2);
            temp[0] = '-';
            my_strcpy(temp + 1, result);
            free(result);
            result = temp;
        }
        *expr = s;
        return result;
    }
    return parse_number(base, expr);
}

static char *parse_term(char const *base, char const *ops,
    char const **expr)
{
    char *left = parse_factor(base, ops, expr);
    char const *s = *expr;
    char *right = NULL;
    char *temp = NULL;

    s = skip_spaces(s);
    while (is_operator(ops, *s, OP_MULT_IDX) ||
           is_operator(ops, *s, OP_DIV_IDX) ||
           is_operator(ops, *s, OP_MOD_IDX)) {
        char op = *s;
        s++;
        right = parse_factor(base, ops, &s);
        if (left == NULL || right == NULL) {
            free(left);
            free(right);
            return NULL;
        }
        if (is_operator(ops, op, OP_MULT_IDX))
            temp = infin_mul(left, right);
        else if (is_operator(ops, op, OP_DIV_IDX))
            temp = infin_div(left, right);
        else
            temp = infin_mod(left, right);
        free(left);
        free(right);
        left = temp;
        s = skip_spaces(s);
    }
    *expr = s;
    return left;
}

static char *parse_expression(char const *base, char const *ops,
    char const **expr)
{
    char *left = parse_term(base, ops, expr);
    char const *s = *expr;
    char *right = NULL;
    char *temp = NULL;

    s = skip_spaces(s);
    while (is_operator(ops, *s, OP_PLUS_IDX) ||
           is_operator(ops, *s, OP_SUB_IDX)) {
        char op = *s;
        s++;
        right = parse_term(base, ops, &s);
        if (left == NULL || right == NULL) {
            free(left);
            free(right);
            return NULL;
        }
        if (is_operator(ops, op, OP_PLUS_IDX))
            temp = infin_add(left, right);
        else
            temp = infin_sub(left, right);
        free(left);
        free(right);
        left = temp;
        s = skip_spaces(s);
    }
    *expr = s;
    return left;
}

char *eval_expr(char const *base, char const *ops,
    char const *expr, unsigned int size)
{
    char *result;
    char const *s = expr;

    (void)size;
    if (base == NULL || ops == NULL || expr == NULL)
        return my_strdup(SYNTAX_ERROR_MSG);
    result = parse_expression(base, ops, &s);
    if (result == NULL)
        return my_strdup(SYNTAX_ERROR_MSG);
    return result;
}
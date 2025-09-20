#include "../include/eval_expr.h"

static int is_space_char(char c)
{
    return c == ' ' || c == '\t' || c == '\n' ||
           c == '\r' || c == '\v' || c == '\f';
}

static void skip_spaces(char const **str)
{
    while (is_space_char(**str))
        (*str)++;
}

static long long parse_expression(char const **str);
static long long parse_term(char const **str);
static long long parse_factor(char const **str);
static long long parse_number(char const **str);

static long long parse_number(char const **str)
{
    long long value = 0;

    skip_spaces(str);
    while (**str >= '0' && **str <= '9') {
        value = value * 10 + (**str - '0');
        (*str)++;
    }
    return value;
}

static long long parse_factor(char const **str)
{
    long long sign = 1;
    long long value;

    skip_spaces(str);
    while (**str == '+' || **str == '-') {
        if (**str == '-')
            sign = -sign;
        (*str)++;
        skip_spaces(str);
    }
    if (**str == '(') {
        (*str)++;
        value = parse_expression(str);
        skip_spaces(str);
        if (**str == ')')
            (*str)++;
    } else {
        value = parse_number(str);
    }
    return sign * value;
}

static long long parse_term(char const **str)
{
    long long value = parse_factor(str);

    while (1) {
        skip_spaces(str);
        if (**str == '*') {
            (*str)++;
            value *= parse_factor(str);
        } else if (**str == '/') {
            (*str)++;
            value /= parse_factor(str);
        } else if (**str == '%') {
            (*str)++;
            value %= parse_factor(str);
        } else {
            break;
        }
    }
    return value;
}

static long long parse_expression(char const **str)
{
    long long value = parse_term(str);

    while (1) {
        skip_spaces(str);
        if (**str == '+') {
            (*str)++;
            value += parse_term(str);
        } else if (**str == '-') {
            (*str)++;
            value -= parse_term(str);
        } else {
            break;
        }
    }
    return value;
}

int eval_expr(char const *str)
{
    char const *cursor = str;
    long long result = parse_expression(&cursor);

    return (int)result;
}

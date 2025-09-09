#include "eval_expr.h"

static int skip_spaces(char const *str, int *pos)
{
    while (str[*pos] == ' ' || str[*pos] == '\t')
        (*pos)++;
    return 0;
}

static int parse_number(char const *str, int *pos)
{
    int result = 0;
    int sign = 1;
    
    skip_spaces(str, pos);
    
    if (str[*pos] == '-') {
        sign = -1;
        (*pos)++;
    } else if (str[*pos] == '+') {
        (*pos)++;
    }
    
    while (str[*pos] >= '0' && str[*pos] <= '9') {
        result = result * 10 + (str[*pos] - '0');
        (*pos)++;
    }
    
    return result * sign;
}

static int parse_factor(char const *str, int *pos);
static int parse_term(char const *str, int *pos);
static int parse_expression(char const *str, int *pos);

static int parse_factor(char const *str, int *pos)
{
    int result = 0;
    
    skip_spaces(str, pos);
    
    if (str[*pos] == '(') {
        (*pos)++;
        result = parse_expression(str, pos);
        skip_spaces(str, pos);
        if (str[*pos] == ')')
            (*pos)++;
        return result;
    } else {
        return parse_number(str, pos);
    }
}

static int parse_term(char const *str, int *pos)
{
    int result = parse_factor(str, pos);
    
    while (1) {
        skip_spaces(str, pos);
        
        if (str[*pos] == '*') {
            (*pos)++;
            result = result * parse_factor(str, pos);
        } else if (str[*pos] == '/') {
            (*pos)++;
            result = result / parse_factor(str, pos);
        } else if (str[*pos] == '%') {
            (*pos)++;
            result = result % parse_factor(str, pos);
        } else {
            break;
        }
    }
    
    return result;
}

static int parse_expression(char const *str, int *pos)
{
    int result = parse_term(str, pos);
    
    while (1) {
        skip_spaces(str, pos);
        
        if (str[*pos] == '+') {
            (*pos)++;
            result = result + parse_term(str, pos);
        } else if (str[*pos] == '-') {
            (*pos)++;
            result = result - parse_term(str, pos);
        } else {
            break;
        }
    }
    
    return result;
}

int eval_expr(char const *str)
{
    int pos = 0;
    
    if (str == 0)
        return 0;
    
    return parse_expression(str, &pos);
}
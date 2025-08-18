#include "eval_expr.h"

int number(char const *str, int *pos)
{
    skip_spaces(str, pos);
    return my_getnbr(str, pos);
}

int factor(char const *str, int *pos)
{
    int result;
    
    skip_spaces(str, pos);
    
    if (str[*pos] == '(') {
        (*pos)++;
        result = expr(str, pos);
        skip_spaces(str, pos);
        if (str[*pos] == ')')
            (*pos)++;
        return result;
    }
    
    return number(str, pos);
}

int term(char const *str, int *pos)
{
    int left = factor(str, pos);
    
    while (1) {
        skip_spaces(str, pos);
        
        if (str[*pos] == '*') {
            (*pos)++;
            left = left * factor(str, pos);
        } else if (str[*pos] == '/') {
            (*pos)++;
            left = left / factor(str, pos);
        } else if (str[*pos] == '%') {
            (*pos)++;
            left = left % factor(str, pos);
        } else {
            break;
        }
    }
    
    return left;
}

int expr(char const *str, int *pos)
{
    int left = term(str, pos);
    
    while (1) {
        skip_spaces(str, pos);
        
        if (str[*pos] == '+') {
            (*pos)++;
            left = left + term(str, pos);
        } else if (str[*pos] == '-') {
            (*pos)++;
            left = left - term(str, pos);
        } else {
            break;
        }
    }
    
    return left;
}

int eval_expr(char const *str)
{
    int pos = 0;
    
    if (!str)
        return 0;
    
    return expr(str, &pos);
}
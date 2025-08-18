#include <stdlib.h>
#include "bistromatic.h"

static void skip_spaces(char const *expr, int *pos)
{
    while (expr[*pos] == ' ' || expr[*pos] == '\t')
        (*pos)++;
}

char *parse_number(char const *expr, char const *base, char const *ops, int *pos)
{
    int start = *pos;
    int len = 0;
    char *result;
    int i;
    
    skip_spaces(expr, pos);
    
    if (expr[*pos] == ops[OP_SUB_IDX]) {
        (*pos)++;
        len++;
    }
    
    while (expr[*pos] && char_to_int(expr[*pos], base) >= 0) {
        (*pos)++;
        len++;
    }
    
    if (len == 0 || (len == 1 && expr[start] == ops[OP_SUB_IDX]))
        return NULL;
    
    result = malloc(len + 1);
    if (!result)
        return NULL;
    
    for (i = 0; i < len; i++)
        result[i] = expr[start + i];
    result[len] = '\0';
    
    return result;
}

char *parse_factor(char const *expr, char const *base, char const *ops, int *pos)
{
    char *result;
    
    skip_spaces(expr, pos);
    
    if (expr[*pos] == ops[OP_OPEN_PARENT_IDX]) {
        (*pos)++;
        result = parse_expression(expr, base, ops);
        skip_spaces(expr, pos);
        if (expr[*pos] != ops[OP_CLOSE_PARENT_IDX])
            return NULL;
        (*pos)++;
        return result;
    }
    
    return parse_number(expr, base, ops, pos);
}

char *parse_term(char const *expr, char const *base, char const *ops, int *pos)
{
    char *left = parse_factor(expr, base, ops, pos);
    char *right, *temp;
    
    if (!left)
        return NULL;
    
    while (1) {
        skip_spaces(expr, pos);
        
        if (expr[*pos] == ops[OP_MULT_IDX]) {
            (*pos)++;
            right = parse_factor(expr, base, ops, pos);
            if (!right) {
                free(left);
                return NULL;
            }
            temp = bigint_mul(left, right, base);
            free(left);
            free(right);
            left = temp;
        } else if (expr[*pos] == ops[OP_DIV_IDX]) {
            (*pos)++;
            right = parse_factor(expr, base, ops, pos);
            if (!right) {
                free(left);
                return NULL;
            }
            temp = bigint_div(left, right, base);
            free(left);
            free(right);
            left = temp;
        } else if (expr[*pos] == ops[OP_MOD_IDX]) {
            (*pos)++;
            right = parse_factor(expr, base, ops, pos);
            if (!right) {
                free(left);
                return NULL;
            }
            temp = bigint_mod(left, right, base);
            free(left);
            free(right);
            left = temp;
        } else {
            break;
        }
    }
    
    return left;
}

char *parse_expression(char const *expr, char const *base, char const *ops)
{
    int pos = 0;
    char *left = parse_term(expr, base, ops, &pos);
    char *right, *temp;
    
    if (!left)
        return NULL;
    
    while (expr[pos]) {
        skip_spaces(expr, &pos);
        
        if (expr[pos] == ops[OP_PLUS_IDX]) {
            pos++;
            right = parse_term(expr, base, ops, &pos);
            if (!right) {
                free(left);
                return NULL;
            }
            temp = bigint_add(left, right, base);
            free(left);
            free(right);
            left = temp;
        } else if (expr[pos] == ops[OP_SUB_IDX]) {
            pos++;
            right = parse_term(expr, base, ops, &pos);
            if (!right) {
                free(left);
                return NULL;
            }
            temp = bigint_sub(left, right, base);
            free(left);
            free(right);
            left = temp;
        } else {
            break;
        }
    }
    
    return left;
}
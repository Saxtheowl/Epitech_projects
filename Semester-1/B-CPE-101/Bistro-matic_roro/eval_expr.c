#include <stdlib.h>
#include "bistromatic.h"

static int validate_expression(char const *expr, char const *base, char const *ops, unsigned int size)
{
    unsigned int i = 0;
    int paren_count = 0;
    
    while (i < size && expr[i]) {
        char c = expr[i];
        
        if (c == ops[OP_OPEN_PARENT_IDX]) {
            paren_count++;
        } else if (c == ops[OP_CLOSE_PARENT_IDX]) {
            paren_count--;
            if (paren_count < 0)
                return 0;
        } else if (char_to_int(c, base) < 0 && 
                   c != ops[OP_PLUS_IDX] && 
                   c != ops[OP_SUB_IDX] &&
                   c != ops[OP_MULT_IDX] && 
                   c != ops[OP_DIV_IDX] && 
                   c != ops[OP_MOD_IDX] &&
                   c != ' ' && c != '\t') {
            return 0;
        }
        i++;
    }
    
    return (paren_count == 0);
}

char *eval_expr(char const *base, char const *ops, char const *expr, unsigned int size)
{
    char *result;
    char *error_result;
    
    if (!base || !ops || !expr) {
        error_result = malloc(my_strlen(ERROR_MSG) + 1);
        if (!error_result)
            return NULL;
        int i = 0;
        while (ERROR_MSG[i]) {
            error_result[i] = ERROR_MSG[i];
            i++;
        }
        error_result[i] = '\0';
        return error_result;
    }
    
    if (!validate_expression(expr, base, ops, size)) {
        error_result = malloc(my_strlen(SYNTAX_ERROR_MSG) + 1);
        if (!error_result)
            return NULL;
        int i = 0;
        while (SYNTAX_ERROR_MSG[i]) {
            error_result[i] = SYNTAX_ERROR_MSG[i];
            i++;
        }
        error_result[i] = '\0';
        return error_result;
    }
    
    result = parse_expression(expr, base, ops);
    
    if (!result) {
        error_result = malloc(my_strlen(SYNTAX_ERROR_MSG) + 1);
        if (!error_result)
            return NULL;
        int i = 0;
        while (SYNTAX_ERROR_MSG[i]) {
            error_result[i] = SYNTAX_ERROR_MSG[i];
            i++;
        }
        error_result[i] = '\0';
        return error_result;
    }
    
    return result;
}
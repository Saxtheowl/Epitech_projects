#include "bistromatic.h"
#include "utils.h"
#include "parser.h"
#include "bigint.h"

char *eval_expr(char const *base, char const *ops,
                char const *expr, unsigned int size)
{
    parser_t parser;
    big_t *value;
    char *result;
    unsigned int length = size;

    if (!base || !ops || !expr)
        fatal_error(ERROR_MSG);
    if (length == 0)
        length = (unsigned int)my_strlen(expr);
    parser_init(&parser, expr, length, base, ops);
    value = parse_expression(&parser);
    result = big_to_base_string(value, base, parser.base_len, ops[OP_SUB_IDX]);
    big_free(value);
    return result;
}

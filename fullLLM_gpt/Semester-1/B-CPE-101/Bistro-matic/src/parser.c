#include <stdlib.h>
#include "bistromatic.h"
#include "utils.h"
#include "parser.h"

static big_t *parse_expr_internal(parser_t *parser);
static big_t *parse_term(parser_t *parser);
static big_t *parse_factor(parser_t *parser);
static big_t *parse_number(parser_t *parser);

static void skip_spaces(parser_t *parser)
{
    while (parser->pos < parser->len && is_space(parser->expr[parser->pos]))
        parser->pos += 1;
}

void parser_syntax_error(parser_t *parser)
{
    (void)parser;
    my_puterr(SYNTAX_ERROR_MSG);
    exit(ERROR_CODE);
}

static char current_char(parser_t *parser)
{
    if (parser->pos >= parser->len)
        return '\0';
    return parser->expr[parser->pos];
}

static int is_digit_char(parser_t *parser, char c)
{
    return parser->char_map[(unsigned char)c] >= 0;
}

static char consume_char(parser_t *parser)
{
    char c = current_char(parser);

    if (c != '\0')
        parser->pos += 1;
    return c;
}

void parser_init(parser_t *parser, const char *expr, unsigned int len,
                 const char *base, const char *ops)
{
    parser->expr = expr;
    parser->len = len;
    parser->pos = 0;
    parser->base = base;
    parser->base_len = (unsigned int)my_strlen(base);
    for (int i = 0; i < 256; ++i)
        parser->char_map[i] = -1;
    for (unsigned int i = 0; i < parser->base_len; ++i) {
        unsigned char ch = (unsigned char)base[i];
        if (parser->char_map[ch] != -1)
            parser_syntax_error(parser);
        parser->char_map[ch] = (int)i;
    }
    for (int i = 0; i < 7; ++i) {
        char op = ops[i];
        parser->ops[i] = op;
        if (parser->char_map[(unsigned char)op] != -1)
            parser_syntax_error(parser);
        for (int j = 0; j < i; ++j) {
            if (parser->ops[j] == op)
                parser_syntax_error(parser);
        }
    }
}

static void expect_char(parser_t *parser, char expected)
{
    skip_spaces(parser);
    if (consume_char(parser) != expected)
        parser_syntax_error(parser);
}

static big_t *parse_number(parser_t *parser)
{
    size_t start;
    size_t length;

    skip_spaces(parser);
    start = parser->pos;
    while (parser->pos < parser->len &&
           is_digit_char(parser, parser->expr[parser->pos]))
        parser->pos += 1;
    length = parser->pos - start;
    if (length == 0)
        parser_syntax_error(parser);
    char *digits = my_strndup(parser->expr + start, length);
    big_t *value = big_from_base_digits(parser->base, parser->char_map,
                                        digits, length);
    free(digits);
    return value;
}

static big_t *parse_factor(parser_t *parser)
{
    int sign = 1;
    big_t *value = NULL;

    skip_spaces(parser);
    while (1) {
        char c = current_char(parser);
        if (c == parser->ops[OP_PLUS_IDX]) {
            consume_char(parser);
        } else if (c == parser->ops[OP_SUB_IDX]) {
            consume_char(parser);
            sign = -sign;
        } else {
            break;
        }
        skip_spaces(parser);
    }
    if (current_char(parser) == parser->ops[OP_OPEN_PARENT_IDX]) {
        consume_char(parser);
        value = parse_expr_internal(parser);
        expect_char(parser, parser->ops[OP_CLOSE_PARENT_IDX]);
    } else {
        if (current_char(parser) == '\0')
            parser_syntax_error(parser);
        value = parse_number(parser);
    }
    if (sign < 0 && !big_is_zero(value))
        value->sign = -value->sign;
    return value;
}

static big_t *apply_operation(big_t *left, big_t *right, char op, parser_t *parser)
{
    big_t *result = NULL;

    if (op == parser->ops[OP_PLUS_IDX])
        result = big_add(left, right);
    else if (op == parser->ops[OP_SUB_IDX])
        result = big_sub(left, right);
    else if (op == parser->ops[OP_MULT_IDX])
        result = big_mul(left, right);
    else if (op == parser->ops[OP_DIV_IDX]) {
        if (big_is_zero(right)) {
            my_puterr(ERROR_MSG);
            exit(EXIT_DIVZERO);
        }
        result = big_div(left, right);
    } else if (op == parser->ops[OP_MOD_IDX]) {
        if (big_is_zero(right)) {
            my_puterr(ERROR_MSG);
            exit(EXIT_DIVZERO);
        }
        result = big_mod(left, right);
    }
    if (!result)
        parser_syntax_error(parser);
    big_free(left);
    big_free(right);
    return result;
}

static big_t *parse_term(parser_t *parser)
{
    big_t *left = parse_factor(parser);

    while (1) {
        skip_spaces(parser);
        char c = current_char(parser);
        if (c == parser->ops[OP_MULT_IDX] ||
            c == parser->ops[OP_DIV_IDX] ||
            c == parser->ops[OP_MOD_IDX]) {
            consume_char(parser);
            big_t *right = parse_factor(parser);
            left = apply_operation(left, right, c, parser);
        } else {
            break;
        }
    }
    return left;
}

static big_t *parse_expr_internal(parser_t *parser)
{
    big_t *left = parse_term(parser);

    while (1) {
        skip_spaces(parser);
        char c = current_char(parser);
        if (c == parser->ops[OP_PLUS_IDX] ||
            c == parser->ops[OP_SUB_IDX]) {
            consume_char(parser);
            big_t *right = parse_term(parser);
            left = apply_operation(left, right, c, parser);
        } else {
            break;
        }
    }
    return left;
}

big_t *parse_expression(parser_t *parser)
{
    parser->pos = 0;
    big_t *value = parse_expr_internal(parser);
    skip_spaces(parser);
    if (parser->pos < parser->len)
        parser_syntax_error(parser);
    return value;
}

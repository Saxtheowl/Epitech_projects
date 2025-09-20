#ifndef PARSER_H
#define PARSER_H

#include "bigint.h"

typedef struct {
    const char *expr;
    unsigned int len;
    unsigned int pos;
    const char *base;
    unsigned int base_len;
    char ops[7];
    int char_map[256];
} parser_t;

void parser_init(parser_t *parser, const char *expr, unsigned int len,
                 const char *base, const char *ops);
big_t *parse_expression(parser_t *parser);
void parser_syntax_error(parser_t *parser);

#endif

#ifndef BISTROMATIC_H
#define BISTROMATIC_H

#define OP_OPEN_PARENT_IDX  0
#define OP_CLOSE_PARENT_IDX 1
#define OP_PLUS_IDX         2
#define OP_SUB_IDX          3
#define OP_NEG_IDX          3
#define OP_MULT_IDX         4
#define OP_DIV_IDX          5
#define OP_MOD_IDX          6

#define EXIT_USAGE    84
#define EXIT_BASE     84
#define EXIT_SIZE_NEG 84
#define EXIT_MALLOC   84
#define EXIT_READ     84
#define EXIT_OPS      84
#define EXIT_SUCCESS  0

#define SYNTAX_ERROR_MSG "syntax error"
#define ERROR_MSG        "error"

char *eval_expr(char const *base, char const *ops,
		char const *expr, unsigned int size);

void my_putstr(char const *str);
int my_strlen(char const *str);
int my_atoi(char const *str);

char *bigint_add(char const *nb1, char const *nb2, char const *base);
char *bigint_sub(char const *nb1, char const *nb2, char const *base);
char *bigint_mul(char const *nb1, char const *nb2, char const *base);
char *bigint_div(char const *nb1, char const *nb2, char const *base);
char *bigint_mod(char const *nb1, char const *nb2, char const *base);

int char_to_int(char c, char const *base);
char int_to_char(int val, char const *base);
char *remove_leading_zeros(char *nb, char const *base);
int is_negative(char const *nb, char const *base);
char *negate_number(char const *nb, char const *base);
int compare_abs(char const *nb1, char const *nb2, char const *base);

char *parse_expression(char const *expr, char const *base, char const *ops);
char *parse_term(char const *expr, char const *base, char const *ops, int *pos);
char *parse_factor(char const *expr, char const *base, char const *ops, int *pos);
char *parse_number(char const *expr, char const *base, char const *ops, int *pos);

#endif
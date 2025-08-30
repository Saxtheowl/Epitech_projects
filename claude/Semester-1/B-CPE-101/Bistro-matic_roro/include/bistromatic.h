/*
** EPITECH PROJECT, 2024
** bistromatic.h
** File description:
** Header file for bistromatic calculator
*/

#ifndef BISTROMATIC_H_
    #define BISTROMATIC_H_

#include <stddef.h>

#define OP_OPEN_PARENT_IDX  0
#define OP_CLOSE_PARENT_IDX 1
#define OP_PLUS_IDX         2
#define OP_SUB_IDX          3
#define OP_NEG_IDX          3
#define OP_MULT_IDX         4
#define OP_DIV_IDX          5
#define OP_MOD_IDX          6

#define EXIT_SUCCESS  0
#define EXIT_USAGE    84
#define EXIT_BASE     84
#define EXIT_SIZE_NEG 84
#define EXIT_MALLOC   84
#define EXIT_READ     84
#define EXIT_OPS      84

#define SYNTAX_ERROR_MSG "syntax error"
#define ERROR_MSG        "error"

char *eval_expr(char const *base, char const *ops,
    char const *expr, unsigned int size);

void my_putstr(char const *str);
int my_strlen(char const *str);
int my_atoi(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *str);

char *infin_add(char const *nb1, char const *nb2);
char *infin_sub(char const *nb1, char const *nb2);
char *infin_mul(char const *nb1, char const *nb2);
char *infin_div(char const *nb1, char const *nb2);
char *infin_mod(char const *nb1, char const *nb2);

char *convert_to_decimal(char const *base, char const *num);
char *convert_from_decimal(char const *base, char const *num);
int get_digit_value(char const *base, char c);
char get_char_from_value(char const *base, int value);

char *remove_leading_zeros(char *str);
int is_valid_number(char const *base, char const *num);
int compare_absolute(char const *nb1, char const *nb2);

#endif /* !BISTROMATIC_H_ */
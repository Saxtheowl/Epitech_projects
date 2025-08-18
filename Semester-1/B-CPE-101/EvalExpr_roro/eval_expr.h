#ifndef EVAL_EXPR_H
#define EVAL_EXPR_H

int eval_expr(char const *str);
void my_putchar(char c);
void my_put_nbr(int nb);
int my_strlen(char const *str);
int my_atoi(char const *str);
int my_getnbr(char const *str, int *pos);

int expr(char const *str, int *pos);
int term(char const *str, int *pos);
int factor(char const *str, int *pos);
int number(char const *str, int *pos);

void skip_spaces(char const *str, int *pos);

#endif
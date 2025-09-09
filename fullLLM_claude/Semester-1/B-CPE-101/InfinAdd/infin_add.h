#ifndef INFIN_ADD_H
#define INFIN_ADD_H

#include <stdlib.h>
#include <unistd.h>

char *my_strdup(char const *str);
int my_strlen(char const *str);
void my_putstr(char const *str);
char *remove_leading_zeros(char *str);
char *add_positive_numbers(char const *num1, char const *num2);
char *subtract_positive_numbers(char const *num1, char const *num2);
int compare_absolute_values(char const *num1, char const *num2);
char *infin_add(char const *num1, char const *num2);

#endif
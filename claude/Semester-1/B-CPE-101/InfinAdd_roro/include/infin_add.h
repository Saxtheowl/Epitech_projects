/*
** EPITECH PROJECT, 2024
** infin_add.h
** File description:
** Header file for infinite addition
*/

#ifndef INFIN_ADD_H_
    #define INFIN_ADD_H_

#include <stddef.h>

char *infin_add(char const *nb1, char const *nb2);
char *add_positive(char const *nb1, char const *nb2);
char *subtract_positive(char const *nb1, char const *nb2);
int compare_absolute(char const *nb1, char const *nb2);
char *remove_leading_zeros(char *str);
int my_strlen(char const *str);
char *my_strdup(char const *str);
char *my_strcpy(char *dest, char const *src);
void my_putstr(char const *str);
void my_putchar(char c);

#endif /* !INFIN_ADD_H_ */
#ifndef MY_H
#define MY_H

#include <stdarg.h>

int mini_printf(const char *format, ...);
int my_putchar(char c);
int my_putstr(char const *str);
int my_put_nbr(int nb);
int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);

#endif
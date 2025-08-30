/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** Header file for my_printf library
*/

#ifndef MY_H_
    #define MY_H_

#include <stdarg.h>
#include <stddef.h>

int my_printf(char const *format, ...);
int my_putchar(char c);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_put_nbr(int nb);
int my_put_unsigned_nbr(unsigned int nb);
int my_put_nbr_base(int nbr, char const *base);
int my_put_unsigned_nbr_base(unsigned int nbr, char const *base);
char *my_strcpy(char *dest, char const *src);

typedef struct format_spec_s {
    char specifier;
    int (*handler)(va_list *args);
} format_spec_t;

int handle_char(va_list *args);
int handle_string(va_list *args);
int handle_int(va_list *args);
int handle_unsigned(va_list *args);
int handle_octal(va_list *args);
int handle_hex_lower(va_list *args);
int handle_hex_upper(va_list *args);
int handle_percent(va_list *args);

#endif /* !MY_H_ */
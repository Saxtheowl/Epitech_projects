#ifndef MY_H
#define MY_H

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
    int minus;
    int plus;
    int space;
    int hash;
    int zero;
    int width;
    int precision;
    int has_precision;
    char length;
    char specifier;
} format_t;

int my_printf(const char *format, ...);
int my_putchar(char c);
int my_putstr(char *str);
int my_putstr_non_printable(char *str);
int my_putnbr(int nb);
int my_putnbr_base(int nb, char *base);
int my_putnbr_unsigned(unsigned int nb);
int my_putnbr_unsigned_base(unsigned int nb, char *base);
int my_putnbr_long(long nb);
int my_putnbr_long_base(long nb, char *base);
int my_putnbr_unsigned_long(unsigned long nb);
int my_putnbr_unsigned_long_base(unsigned long nb, char *base);

int my_strlen(char *str);
char *my_strcpy(char *dest, char *src);
int my_strcmp(char *s1, char *s2);
char *my_strdup(char *src);
void *my_memset(void *s, int c, int n);

int parse_format(const char *format, format_t *fmt);
int handle_format(format_t *fmt, va_list args);
int apply_width_padding(int len, format_t *fmt, char pad_char);
int print_with_flags(char *str, int len, format_t *fmt);
int print_number_with_flags(char *str, int len, format_t *fmt, int is_negative);

#endif
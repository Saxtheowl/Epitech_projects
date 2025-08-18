#ifndef MY_H
#define MY_H

#include <stdarg.h>

int my_printf(char const *format, ...);
int my_putchar(char c);
int my_putstr(char const *str);
int my_put_nbr(int nb);
int my_put_unsigned_nbr(unsigned int nb);
int my_put_nbr_base(long long nb, char const *base);
int my_put_ptr(void *ptr);
int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);

typedef struct {
    int width;
    int precision;
    int left_align;
    int zero_pad;
    int show_sign;
    int space_sign;
    int alternate;
    int precision_set;
} format_flags_t;

int parse_flags(char const *format, int *pos, format_flags_t *flags);
int handle_format(char const *format, int *pos, va_list args);
int print_char(va_list args, format_flags_t *flags);
int print_string(va_list args, format_flags_t *flags);
int print_int(va_list args, format_flags_t *flags);
int print_unsigned(va_list args, format_flags_t *flags);
int print_hex_lower(va_list args, format_flags_t *flags);
int print_hex_upper(va_list args, format_flags_t *flags);
int print_octal(va_list args, format_flags_t *flags);
int print_pointer(va_list args, format_flags_t *flags);
int print_percent(format_flags_t *flags);

int print_padding(int count, char pad_char);
int get_number_len(long long nb, int base);

#endif
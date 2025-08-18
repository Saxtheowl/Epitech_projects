#include <stdarg.h>
#include "my.h"

static void init_flags(format_flags_t *flags)
{
    flags->width = 0;
    flags->precision = -1;
    flags->left_align = 0;
    flags->zero_pad = 0;
    flags->show_sign = 0;
    flags->space_sign = 0;
    flags->alternate = 0;
    flags->precision_set = 0;
}

static int parse_number(char const *format, int *pos)
{
    int num = 0;
    
    while (format[*pos] >= '0' && format[*pos] <= '9') {
        num = num * 10 + (format[*pos] - '0');
        (*pos)++;
    }
    return num;
}

int parse_flags(char const *format, int *pos, format_flags_t *flags)
{
    init_flags(flags);
    
    while (format[*pos] == '-' || format[*pos] == '0' || format[*pos] == '+' ||
           format[*pos] == ' ' || format[*pos] == '#') {
        if (format[*pos] == '-')
            flags->left_align = 1;
        else if (format[*pos] == '0')
            flags->zero_pad = 1;
        else if (format[*pos] == '+')
            flags->show_sign = 1;
        else if (format[*pos] == ' ')
            flags->space_sign = 1;
        else if (format[*pos] == '#')
            flags->alternate = 1;
        (*pos)++;
    }
    
    if (format[*pos] >= '1' && format[*pos] <= '9') {
        flags->width = parse_number(format, pos);
    }
    
    if (format[*pos] == '.') {
        (*pos)++;
        flags->precision_set = 1;
        flags->precision = parse_number(format, pos);
    }
    
    if (flags->left_align)
        flags->zero_pad = 0;
    
    return 0;
}

int handle_format(char const *format, int *pos, va_list args)
{
    format_flags_t flags;
    
    parse_flags(format, pos, &flags);
    
    switch (format[*pos]) {
        case 'c':
            (*pos)++;
            return print_char(args, &flags);
        case 's':
            (*pos)++;
            return print_string(args, &flags);
        case 'd':
        case 'i':
            (*pos)++;
            return print_int(args, &flags);
        case 'u':
            (*pos)++;
            return print_unsigned(args, &flags);
        case 'x':
            (*pos)++;
            return print_hex_lower(args, &flags);
        case 'X':
            (*pos)++;
            return print_hex_upper(args, &flags);
        case 'o':
            (*pos)++;
            return print_octal(args, &flags);
        case 'p':
            (*pos)++;
            return print_pointer(args, &flags);
        case '%':
            (*pos)++;
            return print_percent(&flags);
        default:
            (*pos)++;
            return my_putchar(format[*pos - 1]);
    }
}
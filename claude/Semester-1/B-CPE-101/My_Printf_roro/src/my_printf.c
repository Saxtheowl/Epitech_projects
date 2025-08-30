/*
** EPITECH PROJECT, 2024
** my_printf.c
** File description:
** printf-like function implementation
*/

#include "../include/my.h"

static format_spec_t format_specs[] = {
    {'c', handle_char},
    {'s', handle_string},
    {'d', handle_int},
    {'i', handle_int},
    {'u', handle_unsigned},
    {'o', handle_octal},
    {'x', handle_hex_lower},
    {'X', handle_hex_upper},
    {'%', handle_percent},
    {'\0', NULL}
};

static int handle_format_specifier(char spec, va_list *args)
{
    int i = 0;

    while (format_specs[i].specifier != '\0') {
        if (format_specs[i].specifier == spec) {
            return format_specs[i].handler(args);
        }
        i++;
    }
    my_putchar('%');
    my_putchar(spec);
    return 2;
}

int my_printf(char const *format, ...)
{
    va_list args;
    int count = 0;
    int i = 0;

    if (format == NULL)
        return -1;
    va_start(args, format);
    while (format[i]) {
        if (format[i] == '%' && format[i + 1]) {
            i++;
            count += handle_format_specifier(format[i], &args);
        } else {
            my_putchar(format[i]);
            count++;
        }
        i++;
    }
    va_end(args);
    return count;
}
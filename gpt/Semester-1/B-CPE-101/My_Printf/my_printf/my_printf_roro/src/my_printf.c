/*
** EPITECH PROJECT, 2025
** my_printf_roro
** File description:
** Minimal my_printf implementation
*/

#include <stdarg.h>
#include "my_printf.h"

int my_putc(char c);
int my_puts(const char *s);
int my_putnbr(long v);
int my_putun(unsigned long v);
int my_putbase(unsigned long v, const char *digits);

static int handle_fmt(char c, va_list *ap)
{
    if (c == 'c')
        return my_putc((char)va_arg(*ap, int));
    if (c == 's')
        return my_puts(va_arg(*ap, const char *));
    if (c == 'd' || c == 'i')
        return my_putnbr((long)va_arg(*ap, int));
    if (c == 'u')
        return my_putun((unsigned long)va_arg(*ap, unsigned int));
    if (c == 'o')
        return my_putbase((unsigned long)va_arg(*ap, unsigned int), "01234567");
    if (c == 'x')
        return my_putbase((unsigned long)va_arg(*ap, unsigned int), "0123456789abcdef");
    if (c == 'X')
        return my_putbase((unsigned long)va_arg(*ap, unsigned int), "0123456789ABCDEF");
    if (c == '%')
        return my_putc('%');
    return 0;
}

int my_printf(const char *fmt, ...)
{
    va_list ap;
    int count;
    int i;

    va_start(ap, fmt);
    count = 0;
    for (i = 0; fmt && fmt[i]; ++i) {
        if (fmt[i] == '%') {
            ++i;
            count += handle_fmt(fmt[i], &ap);
        } else {
            count += my_putc(fmt[i]);
        }
    }
    va_end(ap);
    return count;
}

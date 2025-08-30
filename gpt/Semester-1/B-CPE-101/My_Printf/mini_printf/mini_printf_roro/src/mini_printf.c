/*
** EPITECH PROJECT, 2025
** mini_printf_roro
** File description:
** Minimal printf: %c %s %d %i and %%
*/

#include <stdarg.h>
#include "mini_printf.h"

int mp_putc(char c);
int mp_puts(const char *s);
int mp_putnbr(long v);

static int handle(char c, va_list *ap)
{
    if (c == 'c')
        return mp_putc((char)va_arg(*ap, int));
    if (c == 's')
        return mp_puts(va_arg(*ap, const char *));
    if (c == 'd' || c == 'i')
        return mp_putnbr((long)va_arg(*ap, int));
    if (c == '%')
        return mp_putc('%');
    return 0;
}

int mini_printf(const char *fmt, ...)
{
    va_list ap;
    int n = 0;
    int i = 0;

    va_start(ap, fmt);
    while (fmt && fmt[i]) {
        if (fmt[i] == '%') {
            i += 1;
            n += handle(fmt[i], &ap);
        } else {
            n += mp_putc(fmt[i]);
        }
        i += 1;
    }
    va_end(ap);
    return n;
}

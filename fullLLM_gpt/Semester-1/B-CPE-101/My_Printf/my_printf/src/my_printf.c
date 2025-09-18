#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include "my_printf.h"

int mp_putc(char c) { return (int)write(1, &c, 1); }

int mp_puts(const char *s)
{
    if (!s) s = "(null)";
    size_t n = 0; while (s[n]) n++;
    if (n) write(1, s, n);
    return (int)n;
}

int mp_putu_base(unsigned long v, const char *digits)
{
    char buf[64]; int i = 0, out = 0; unsigned base = 0;
    while (digits[base]) base++;
    if (v == 0) return mp_putc(digits[0]);
    while (v && i < (int)sizeof(buf)) { buf[i++] = digits[v % base]; v /= base; }
    while (i--) out += mp_putc(buf[i]);
    return out;
}

static int mp_puti(long v)
{
    if (v < 0) return mp_putc('-') + mp_putu_base((unsigned long)(-v), "0123456789");
    return mp_putu_base((unsigned long)v, "0123456789");
}

int vmy_printf(const char *fmt, va_list ap)
{
    int count = 0;
    for (size_t i = 0; fmt && fmt[i]; ++i) {
        if (fmt[i] != '%') { count += mp_putc(fmt[i]); continue; }
        char sp = fmt[++i];
        if (!sp) break;
        switch (sp) {
            case '%': count += mp_putc('%'); break;
            case 's': count += mp_puts(va_arg(ap, const char*)); break;
            case 'c': count += mp_putc((char)va_arg(ap, int)); break;
            case 'd': case 'i': count += mp_puti((long)va_arg(ap, int)); break;
            case 'u': count += mp_putu_base((unsigned long)va_arg(ap, unsigned), "0123456789"); break;
            case 'o': count += mp_putu_base((unsigned long)va_arg(ap, unsigned), "01234567"); break;
            case 'x': count += mp_putu_base((unsigned long)va_arg(ap, unsigned), "0123456789abcdef"); break;
            case 'X': count += mp_putu_base((unsigned long)va_arg(ap, unsigned), "0123456789ABCDEF"); break;
            case 'p': count += mp_puts("0x"); count += mp_putu_base((unsigned long)va_arg(ap, void*), "0123456789abcdef"); break;
            default:  count += mp_putc('%'); count += mp_putc(sp); break;
        }
    }
    return count;
}

int my_printf(const char *fmt, ...)
{
    va_list ap; va_start(ap, fmt);
    int r = vmy_printf(fmt, ap);
    va_end(ap);
    return r;
}


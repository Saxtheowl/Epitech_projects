#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include "mini_printf.h"

static int putstr(const char *s)
{
    if (!s) s = "(null)";
    size_t n = 0; while (s[n]) n++;
    if (n) write(1, s, n);
    return (int)n;
}

static int putchar1(char c)
{
    return (int)write(1, &c, 1);
}

static int putnbr(long val)
{
    char buf[32];
    int i = 0, neg = 0, out = 0;
    if (val == 0) return putchar1('0');
    if (val < 0) { neg = 1; val = -val; }
    while (val && i < (int)sizeof(buf)) { buf[i++] = (char)('0' + (val % 10)); val /= 10; }
    if (neg) out += putchar1('-');
    while (i--) out += putchar1(buf[i]);
    return out;
}

int vmini_printf(const char *fmt, va_list ap)
{
    int count = 0;
    for (size_t i = 0; fmt && fmt[i]; ++i) {
        if (fmt[i] != '%') { count += putchar1(fmt[i]); continue; }
        char sp = fmt[++i];
        if (!sp) break;
        switch (sp) {
            case '%': count += putchar1('%'); break;
            case 's': count += putstr(va_arg(ap, const char*)); break;
            case 'c': count += putchar1((char)va_arg(ap, int)); break;
            case 'd': case 'i': count += putnbr((long)va_arg(ap, int)); break;
            default:  // unknown specifier: print as-is
                count += putchar1('%');
                count += putchar1(sp);
                break;
        }
    }
    return count;
}

int mini_printf(const char *fmt, ...)
{
    va_list ap; va_start(ap, fmt);
    int r = vmini_printf(fmt, ap);
    va_end(ap);
    return r;
}


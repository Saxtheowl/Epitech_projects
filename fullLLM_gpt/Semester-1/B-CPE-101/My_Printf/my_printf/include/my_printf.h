#ifndef MY_PRINTF_H
#define MY_PRINTF_H

#include <stdarg.h>

int my_printf(const char *fmt, ...);
int vmy_printf(const char *fmt, va_list ap);

// internal helpers
int mp_putc(char c);
int mp_puts(const char *s);
int mp_putu_base(unsigned long v, const char *digits);
int mp_puts_s(const char *s);

#endif // MY_PRINTF_H


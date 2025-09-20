#ifndef MY_PRINTF_H
#define MY_PRINTF_H

#include <stdarg.h>

int my_printf(const char *format, ...);
int vmy_printf(const char *format, va_list ap);

#endif

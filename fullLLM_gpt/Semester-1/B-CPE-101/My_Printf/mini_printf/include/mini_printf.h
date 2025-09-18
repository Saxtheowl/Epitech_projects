#ifndef MINI_PRINTF_H
#define MINI_PRINTF_H

#include <stdarg.h>

int mini_printf(const char *fmt, ...);
int vmini_printf(const char *fmt, va_list ap);

#endif // MINI_PRINTF_H


#include "my.h"

int my_printf(const char *format, ...)
{
    va_list args;
    format_t fmt;
    int count = 0;
    int i = 0;
    int len;

    if (!format)
        return -1;

    va_start(args, format);

    while (format[i]) {
        if (format[i] == '%') {
            i++;
            if (format[i] == '%') {
                count += my_putchar('%');
                i++;
                continue;
            }
            len = parse_format(&format[i], &fmt);
            if (len == -1) {
                va_end(args);
                return -1;
            }
            i += len;
            count += handle_format(&fmt, args);
        } else {
            count += my_putchar(format[i]);
            i++;
        }
    }

    va_end(args);
    return count;
}
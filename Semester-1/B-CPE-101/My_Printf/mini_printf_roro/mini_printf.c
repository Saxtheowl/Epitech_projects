#include <stdarg.h>
#include "my.h"

static int handle_format_specifier(const char *format, int *pos, va_list args)
{
    int count = 0;
    
    (*pos)++;
    
    switch (format[*pos]) {
        case 'd':
        case 'i':
            count += my_put_nbr(va_arg(args, int));
            break;
        case 's':
            count += my_putstr(va_arg(args, char *));
            break;
        case 'c':
            count += my_putchar(va_arg(args, int));
            break;
        case '%':
            count += my_putchar('%');
            break;
        default:
            count += my_putchar('%');
            count += my_putchar(format[*pos]);
            break;
    }
    
    (*pos)++;
    return count;
}

int mini_printf(const char *format, ...)
{
    va_list args;
    int pos = 0;
    int count = 0;
    
    if (!format)
        return -1;
    
    va_start(args, format);
    
    while (format[pos]) {
        if (format[pos] == '%') {
            count += handle_format_specifier(format, &pos, args);
        } else {
            count += my_putchar(format[pos]);
            pos++;
        }
    }
    
    va_end(args);
    return count;
}
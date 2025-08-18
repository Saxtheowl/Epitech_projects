#include <stdarg.h>
#include "my.h"

int my_printf(char const *format, ...)
{
    va_list args;
    int pos = 0;
    int count = 0;
    
    if (!format)
        return -1;
    
    va_start(args, format);
    
    while (format[pos]) {
        if (format[pos] == '%') {
            pos++;
            count += handle_format(format, &pos, args);
        } else {
            count += my_putchar(format[pos]);
            pos++;
        }
    }
    
    va_end(args);
    return count;
}
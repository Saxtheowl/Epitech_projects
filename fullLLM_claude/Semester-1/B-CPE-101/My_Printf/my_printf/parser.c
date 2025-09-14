#include "my.h"

static void init_format(format_t *fmt)
{
    fmt->minus = 0;
    fmt->plus = 0;
    fmt->space = 0;
    fmt->hash = 0;
    fmt->zero = 0;
    fmt->width = 0;
    fmt->precision = 0;
    fmt->has_precision = 0;
    fmt->length = 0;
    fmt->specifier = 0;
}

static int parse_flags(const char *format, format_t *fmt)
{
    int i = 0;

    while (format[i] == '-' || format[i] == '+' || format[i] == ' ' ||
           format[i] == '#' || format[i] == '0') {
        if (format[i] == '-')
            fmt->minus = 1;
        else if (format[i] == '+')
            fmt->plus = 1;
        else if (format[i] == ' ')
            fmt->space = 1;
        else if (format[i] == '#')
            fmt->hash = 1;
        else if (format[i] == '0')
            fmt->zero = 1;
        i++;
    }
    return i;
}

static int parse_width(const char *format, format_t *fmt)
{
    int i = 0;

    while (format[i] >= '0' && format[i] <= '9') {
        fmt->width = fmt->width * 10 + (format[i] - '0');
        i++;
    }
    return i;
}

static int parse_precision(const char *format, format_t *fmt)
{
    int i = 0;

    if (format[i] == '.') {
        fmt->has_precision = 1;
        i++;
        while (format[i] >= '0' && format[i] <= '9') {
            fmt->precision = fmt->precision * 10 + (format[i] - '0');
            i++;
        }
    }
    return i;
}

static int parse_length(const char *format, format_t *fmt)
{
    if (format[0] == 'l' || format[0] == 'h') {
        fmt->length = format[0];
        return 1;
    }
    return 0;
}

int parse_format(const char *format, format_t *fmt)
{
    int i = 0;

    init_format(fmt);

    i += parse_flags(&format[i], fmt);
    i += parse_width(&format[i], fmt);
    i += parse_precision(&format[i], fmt);
    i += parse_length(&format[i], fmt);

    if (format[i] == 'd' || format[i] == 'i' || format[i] == 'o' ||
        format[i] == 'u' || format[i] == 'x' || format[i] == 'X' ||
        format[i] == 'c' || format[i] == 's' || format[i] == 'p') {
        fmt->specifier = format[i];
        return i + 1;
    }

    return -1;
}
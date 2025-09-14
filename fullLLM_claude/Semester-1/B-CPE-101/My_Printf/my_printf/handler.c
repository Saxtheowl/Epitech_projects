#include "my.h"

static int handle_char(format_t *fmt, va_list args)
{
    char c = va_arg(args, int);
    int count = 0;

    if (fmt->width > 1 && !fmt->minus) {
        count += apply_width_padding(1, fmt, ' ');
    }
    
    count += my_putchar(c);
    
    if (fmt->width > 1 && fmt->minus) {
        count += apply_width_padding(1, fmt, ' ');
    }
    
    return count;
}

static int handle_string(format_t *fmt, va_list args)
{
    char *str = va_arg(args, char *);
    int len;
    int count = 0;

    if (!str)
        str = "(null)";
    
    len = my_strlen(str);
    
    if (fmt->has_precision && fmt->precision < len)
        len = fmt->precision;

    if (fmt->width > len && !fmt->minus) {
        count += apply_width_padding(len, fmt, ' ');
    }
    
    for (int i = 0; i < len; i++) {
        count += my_putchar(str[i]);
    }
    
    if (fmt->width > len && fmt->minus) {
        count += apply_width_padding(len, fmt, ' ');
    }
    
    return count;
}

static int handle_pointer(format_t *fmt __attribute__((unused)), va_list args)
{
    void *ptr = va_arg(args, void *);
    unsigned long addr = (unsigned long)ptr;
    int count = 0;

    if (!ptr) {
        count += my_putstr("(nil)");
        return count;
    }

    count += my_putstr("0x");
    count += my_putnbr_unsigned_long_base(addr, "0123456789abcdef");
    
    return count;
}

static int handle_decimal(format_t *fmt, va_list args)
{
    long nb;
    int count = 0;

    if (fmt->length == 'l')
        nb = va_arg(args, long);
    else
        nb = va_arg(args, int);

    if (nb < 0) {
        if (fmt->plus || fmt->space) {
            count += my_putchar('-');
        } else {
            count += my_putchar('-');
        }
        if (nb == -2147483648LL) {
            count += my_putstr("2147483648");
            return count;
        }
        nb = -nb;
    } else if (fmt->plus) {
        count += my_putchar('+');
    } else if (fmt->space) {
        count += my_putchar(' ');
    }

    count += my_putnbr_long(nb);
    return count;
}

static int handle_unsigned(format_t *fmt, va_list args)
{
    unsigned long nb;
    int count = 0;

    if (fmt->length == 'l')
        nb = va_arg(args, unsigned long);
    else
        nb = va_arg(args, unsigned int);

    if (fmt->specifier == 'u') {
        count += my_putnbr_unsigned_long(nb);
    } else if (fmt->specifier == 'o') {
        if (fmt->hash && nb != 0)
            count += my_putchar('0');
        count += my_putnbr_unsigned_long_base(nb, "01234567");
    } else if (fmt->specifier == 'x') {
        if (fmt->hash && nb != 0)
            count += my_putstr("0x");
        count += my_putnbr_unsigned_long_base(nb, "0123456789abcdef");
    } else if (fmt->specifier == 'X') {
        if (fmt->hash && nb != 0)
            count += my_putstr("0X");
        count += my_putnbr_unsigned_long_base(nb, "0123456789ABCDEF");
    }

    return count;
}

int handle_format(format_t *fmt, va_list args)
{
    if (fmt->specifier == 'c')
        return handle_char(fmt, args);
    else if (fmt->specifier == 's')
        return handle_string(fmt, args);
    else if (fmt->specifier == 'p')
        return handle_pointer(fmt, args);
    else if (fmt->specifier == 'd' || fmt->specifier == 'i')
        return handle_decimal(fmt, args);
    else if (fmt->specifier == 'u' || fmt->specifier == 'o' ||
             fmt->specifier == 'x' || fmt->specifier == 'X')
        return handle_unsigned(fmt, args);
    
    return 0;
}
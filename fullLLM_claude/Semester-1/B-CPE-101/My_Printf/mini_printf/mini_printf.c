#include <stdarg.h>
#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

int my_putstr(char const *str)
{
    int count = 0;
    
    if (str == 0) {
        my_putstr("(null)");
        return 6;
    }
    
    while (str[count]) {
        my_putchar(str[count]);
        count++;
    }
    return count;
}

int my_put_nbr(int nb)
{
    int count = 0;
    
    if (nb == -2147483648) {
        my_putstr("-2147483648");
        return 11;
    }
    
    if (nb < 0) {
        my_putchar('-');
        count++;
        nb = -nb;
    }
    
    if (nb >= 10) {
        count += my_put_nbr(nb / 10);
    }
    
    my_putchar('0' + nb % 10);
    count++;
    
    return count;
}

int process_flag(char flag, va_list args)
{
    switch (flag) {
        case 'd':
        case 'i':
            return my_put_nbr(va_arg(args, int));
        case 's':
            return my_putstr(va_arg(args, char*));
        case 'c':
            my_putchar(va_arg(args, int));
            return 1;
        case '%':
            my_putchar('%');
            return 1;
        default:
            my_putchar('%');
            my_putchar(flag);
            return 2;
    }
}

int mini_printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    int i = 0;
    
    if (format == 0)
        return -1;
    
    va_start(args, format);
    
    while (format[i]) {
        if (format[i] == '%' && format[i + 1] != '\0') {
            count += process_flag(format[i + 1], args);
            i += 2;
        } else {
            my_putchar(format[i]);
            count++;
            i++;
        }
    }
    
    va_end(args);
    return count;
}
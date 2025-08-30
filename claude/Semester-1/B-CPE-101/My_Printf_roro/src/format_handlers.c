/*
** EPITECH PROJECT, 2024
** format_handlers.c
** File description:
** format specifier handlers for my_printf
*/

#include "../include/my.h"

int handle_char(va_list *args)
{
    char c = va_arg(*args, int);
    
    return my_putchar(c);
}

int handle_string(va_list *args)
{
    char *str = va_arg(*args, char *);
    
    return my_putstr(str);
}

int handle_int(va_list *args)
{
    int nb = va_arg(*args, int);
    
    return my_put_nbr(nb);
}

int handle_unsigned(va_list *args)
{
    unsigned int nb = va_arg(*args, unsigned int);
    
    return my_put_unsigned_nbr_base(nb, "0123456789");
}

int handle_octal(va_list *args)
{
    unsigned int nb = va_arg(*args, unsigned int);
    
    return my_put_unsigned_nbr_base(nb, "01234567");
}

int handle_hex_lower(va_list *args)
{
    unsigned int nb = va_arg(*args, unsigned int);
    
    return my_put_unsigned_nbr_base(nb, "0123456789abcdef");
}

int handle_hex_upper(va_list *args)
{
    unsigned int nb = va_arg(*args, unsigned int);
    
    return my_put_unsigned_nbr_base(nb, "0123456789ABCDEF");
}

int handle_percent(va_list *args)
{
    (void)args;
    return my_putchar('%');
}
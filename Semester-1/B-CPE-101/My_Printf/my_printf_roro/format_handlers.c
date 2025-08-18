#include <stdarg.h>
#include "my.h"

int print_padding(int count, char pad_char)
{
    int printed = 0;
    
    while (count > 0) {
        my_putchar(pad_char);
        printed++;
        count--;
    }
    return printed;
}

int get_number_len(long long nb, int base)
{
    int len = 0;
    
    if (nb == 0)
        return 1;
    if (nb < 0) {
        len = 1;
        nb = -nb;
    }
    while (nb > 0) {
        nb /= base;
        len++;
    }
    return len;
}

int print_char(va_list args, format_flags_t *flags)
{
    char c = va_arg(args, int);
    int count = 0;
    
    if (!flags->left_align && flags->width > 1) {
        count += print_padding(flags->width - 1, ' ');
    }
    
    count += my_putchar(c);
    
    if (flags->left_align && flags->width > 1) {
        count += print_padding(flags->width - 1, ' ');
    }
    
    return count;
}

int print_string(va_list args, format_flags_t *flags)
{
    char *str = va_arg(args, char *);
    int len, print_len, count = 0;
    
    if (!str)
        str = "(null)";
    
    len = my_strlen(str);
    print_len = len;
    
    if (flags->precision_set && flags->precision < len) {
        print_len = flags->precision;
    }
    
    if (!flags->left_align && flags->width > print_len) {
        count += print_padding(flags->width - print_len, ' ');
    }
    
    for (int i = 0; i < print_len; i++) {
        count += my_putchar(str[i]);
    }
    
    if (flags->left_align && flags->width > print_len) {
        count += print_padding(flags->width - print_len, ' ');
    }
    
    return count;
}

int print_int(va_list args, format_flags_t *flags)
{
    int nb = va_arg(args, int);
    int count = 0;
    int len = get_number_len(nb, 10);
    int sign_len = 0;
    char pad_char = (flags->zero_pad && !flags->left_align) ? '0' : ' ';
    
    if (nb < 0 || flags->show_sign || flags->space_sign) {
        sign_len = 1;
    }
    
    if (!flags->left_align && flags->width > len + sign_len) {
        if (pad_char == '0') {
            if (nb < 0) {
                count += my_putchar('-');
            } else if (flags->show_sign) {
                count += my_putchar('+');
            } else if (flags->space_sign) {
                count += my_putchar(' ');
            }
            count += print_padding(flags->width - len - sign_len, '0');
        } else {
            count += print_padding(flags->width - len - sign_len, ' ');
            if (nb < 0) {
                count += my_putchar('-');
            } else if (flags->show_sign) {
                count += my_putchar('+');
            } else if (flags->space_sign) {
                count += my_putchar(' ');
            }
        }
    } else {
        if (nb < 0) {
            count += my_putchar('-');
        } else if (flags->show_sign) {
            count += my_putchar('+');
        } else if (flags->space_sign) {
            count += my_putchar(' ');
        }
    }
    
    if (nb < 0) {
        if (nb == -2147483648) {
            count += my_putstr("2147483648");
        } else {
            count += my_put_unsigned_nbr(-nb);
        }
    } else {
        count += my_put_unsigned_nbr(nb);
    }
    
    if (flags->left_align && flags->width > len + sign_len) {
        count += print_padding(flags->width - len - sign_len, ' ');
    }
    
    return count;
}

int print_unsigned(va_list args, format_flags_t *flags)
{
    unsigned int nb = va_arg(args, unsigned int);
    int count = 0;
    int len = get_number_len(nb, 10);
    char pad_char = (flags->zero_pad && !flags->left_align) ? '0' : ' ';
    
    if (!flags->left_align && flags->width > len) {
        count += print_padding(flags->width - len, pad_char);
    }
    
    count += my_put_unsigned_nbr(nb);
    
    if (flags->left_align && flags->width > len) {
        count += print_padding(flags->width - len, ' ');
    }
    
    return count;
}

int print_hex_lower(va_list args, format_flags_t *flags)
{
    unsigned int nb = va_arg(args, unsigned int);
    int count = 0;
    int len = get_number_len(nb, 16);
    char pad_char = (flags->zero_pad && !flags->left_align) ? '0' : ' ';
    int prefix_len = (flags->alternate && nb != 0) ? 2 : 0;
    
    if (!flags->left_align && flags->width > len + prefix_len) {
        if (pad_char == '0' && prefix_len) {
            count += my_putstr("0x");
            count += print_padding(flags->width - len - prefix_len, '0');
        } else {
            count += print_padding(flags->width - len - prefix_len, ' ');
            if (prefix_len) {
                count += my_putstr("0x");
            }
        }
    } else if (prefix_len) {
        count += my_putstr("0x");
    }
    
    count += my_put_nbr_base(nb, "0123456789abcdef");
    
    if (flags->left_align && flags->width > len + prefix_len) {
        count += print_padding(flags->width - len - prefix_len, ' ');
    }
    
    return count;
}

int print_hex_upper(va_list args, format_flags_t *flags)
{
    unsigned int nb = va_arg(args, unsigned int);
    int count = 0;
    int len = get_number_len(nb, 16);
    char pad_char = (flags->zero_pad && !flags->left_align) ? '0' : ' ';
    int prefix_len = (flags->alternate && nb != 0) ? 2 : 0;
    
    if (!flags->left_align && flags->width > len + prefix_len) {
        if (pad_char == '0' && prefix_len) {
            count += my_putstr("0X");
            count += print_padding(flags->width - len - prefix_len, '0');
        } else {
            count += print_padding(flags->width - len - prefix_len, ' ');
            if (prefix_len) {
                count += my_putstr("0X");
            }
        }
    } else if (prefix_len) {
        count += my_putstr("0X");
    }
    
    count += my_put_nbr_base(nb, "0123456789ABCDEF");
    
    if (flags->left_align && flags->width > len + prefix_len) {
        count += print_padding(flags->width - len - prefix_len, ' ');
    }
    
    return count;
}

int print_octal(va_list args, format_flags_t *flags)
{
    unsigned int nb = va_arg(args, unsigned int);
    int count = 0;
    int len = get_number_len(nb, 8);
    char pad_char = (flags->zero_pad && !flags->left_align) ? '0' : ' ';
    int prefix_len = (flags->alternate && nb != 0) ? 1 : 0;
    
    if (!flags->left_align && flags->width > len + prefix_len) {
        if (pad_char == '0' && prefix_len) {
            count += my_putchar('0');
            count += print_padding(flags->width - len - prefix_len, '0');
        } else {
            count += print_padding(flags->width - len - prefix_len, ' ');
            if (prefix_len) {
                count += my_putchar('0');
            }
        }
    } else if (prefix_len) {
        count += my_putchar('0');
    }
    
    count += my_put_nbr_base(nb, "01234567");
    
    if (flags->left_align && flags->width > len + prefix_len) {
        count += print_padding(flags->width - len - prefix_len, ' ');
    }
    
    return count;
}

int print_pointer(va_list args, format_flags_t *flags)
{
    void *ptr = va_arg(args, void *);
    int count = 0;
    
    (void)flags;
    count += my_put_ptr(ptr);
    
    return count;
}

int print_percent(format_flags_t *flags)
{
    int count = 0;
    
    if (!flags->left_align && flags->width > 1) {
        count += print_padding(flags->width - 1, ' ');
    }
    
    count += my_putchar('%');
    
    if (flags->left_align && flags->width > 1) {
        count += print_padding(flags->width - 1, ' ');
    }
    
    return count;
}
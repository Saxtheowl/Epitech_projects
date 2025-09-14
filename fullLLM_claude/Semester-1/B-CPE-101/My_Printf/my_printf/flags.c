#include "my.h"

int apply_width_padding(int len, format_t *fmt, char pad_char)
{
    int count = 0;
    int padding = fmt->width - len;

    while (padding > 0) {
        count += my_putchar(pad_char);
        padding--;
    }
    
    return count;
}

int print_with_flags(char *str, int len, format_t *fmt)
{
    int count = 0;
    char pad_char = (fmt->zero && !fmt->minus) ? '0' : ' ';

    if (fmt->width > len && !fmt->minus) {
        count += apply_width_padding(len, fmt, pad_char);
    }
    
    count += my_putstr(str);
    
    if (fmt->width > len && fmt->minus) {
        count += apply_width_padding(len, fmt, ' ');
    }
    
    return count;
}

int print_number_with_flags(char *str, int len, format_t *fmt, int is_negative)
{
    int count = 0;
    int sign_len = 0;

    if (is_negative || fmt->plus || fmt->space)
        sign_len = 1;

    if (fmt->width > (len + sign_len) && !fmt->minus && !fmt->zero) {
        count += apply_width_padding(len + sign_len, fmt, ' ');
    }

    if (is_negative) {
        count += my_putchar('-');
    } else if (fmt->plus) {
        count += my_putchar('+');
    } else if (fmt->space) {
        count += my_putchar(' ');
    }

    if (fmt->width > (len + sign_len) && !fmt->minus && fmt->zero) {
        count += apply_width_padding(len + sign_len, fmt, '0');
    }

    count += my_putstr(str);

    if (fmt->width > (len + sign_len) && fmt->minus) {
        count += apply_width_padding(len + sign_len, fmt, ' ');
    }

    return count;
}
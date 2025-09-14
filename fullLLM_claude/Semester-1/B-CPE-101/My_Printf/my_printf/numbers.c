#include "my.h"

int my_putnbr(int nb)
{
    int count = 0;
    
    if (nb < 0) {
        count += my_putchar('-');
        if (nb == -2147483648) {
            count += my_putstr("2147483648");
            return count;
        }
        nb = -nb;
    }
    
    if (nb >= 10) {
        count += my_putnbr(nb / 10);
    }
    
    count += my_putchar('0' + (nb % 10));
    return count;
}

int my_putnbr_unsigned(unsigned int nb)
{
    int count = 0;
    
    if (nb >= 10) {
        count += my_putnbr_unsigned(nb / 10);
    }
    
    count += my_putchar('0' + (nb % 10));
    return count;
}

int my_putnbr_base(int nb, char *base)
{
    int count = 0;
    int base_len = my_strlen(base);
    
    if (nb < 0) {
        count += my_putchar('-');
        nb = -nb;
    }
    
    if (nb >= base_len) {
        count += my_putnbr_base(nb / base_len, base);
    }
    
    count += my_putchar(base[nb % base_len]);
    return count;
}

int my_putnbr_unsigned_base(unsigned int nb, char *base)
{
    int count = 0;
    int base_len = my_strlen(base);
    
    if (nb >= (unsigned int)base_len) {
        count += my_putnbr_unsigned_base(nb / base_len, base);
    }
    
    count += my_putchar(base[nb % base_len]);
    return count;
}

int my_putnbr_long(long nb)
{
    int count = 0;
    
    if (nb < 0) {
        count += my_putchar('-');
        if (nb == (long)-9223372036854775808UL) {
            count += my_putstr("9223372036854775808");
            return count;
        }
        nb = -nb;
    }
    
    if (nb >= 10) {
        count += my_putnbr_long(nb / 10);
    }
    
    count += my_putchar('0' + (nb % 10));
    return count;
}
#include <unistd.h>
#include "my.h"

int my_putchar(char c)
{
    write(1, &c, 1);
    return 1;
}

int my_putstr(char const *str)
{
    int len = 0;
    
    if (!str)
        str = "(null)";
    
    while (str[len]) {
        my_putchar(str[len]);
        len++;
    }
    return len;
}

int my_strlen(char const *str)
{
    int len = 0;
    
    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;
    
    if (!dest || !src)
        return dest;
    
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int my_put_nbr(int nb)
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
        count += my_put_nbr(nb / 10);
    }
    count += my_putchar(nb % 10 + '0');
    return count;
}

int my_put_unsigned_nbr(unsigned int nb)
{
    int count = 0;
    
    if (nb >= 10) {
        count += my_put_unsigned_nbr(nb / 10);
    }
    count += my_putchar(nb % 10 + '0');
    return count;
}

int my_put_nbr_base(long long nb, char const *base)
{
    int count = 0;
    int base_len = my_strlen(base);
    
    if (nb < 0) {
        count += my_putchar('-');
        nb = -nb;
    }
    
    if (nb >= base_len) {
        count += my_put_nbr_base(nb / base_len, base);
    }
    count += my_putchar(base[nb % base_len]);
    return count;
}

int my_put_ptr(void *ptr)
{
    unsigned long addr = (unsigned long)ptr;
    int count = 0;
    
    if (!ptr) {
        return my_putstr("(nil)");
    }
    
    count += my_putstr("0x");
    if (addr == 0) {
        count += my_putchar('0');
    } else {
        count += my_put_nbr_base(addr, "0123456789abcdef");
    }
    return count;
}
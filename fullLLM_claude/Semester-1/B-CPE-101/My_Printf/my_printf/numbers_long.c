#include "my.h"

int my_putnbr_long_base(long nb, char *base)
{
    int count = 0;
    int base_len = my_strlen(base);
    
    if (nb < 0) {
        count += my_putchar('-');
        nb = -nb;
    }
    
    if (nb >= base_len) {
        count += my_putnbr_long_base(nb / base_len, base);
    }
    
    count += my_putchar(base[nb % base_len]);
    return count;
}

int my_putnbr_unsigned_long(unsigned long nb)
{
    int count = 0;
    
    if (nb >= 10) {
        count += my_putnbr_unsigned_long(nb / 10);
    }
    
    count += my_putchar('0' + (nb % 10));
    return count;
}

int my_putnbr_unsigned_long_base(unsigned long nb, char *base)
{
    int count = 0;
    int base_len = my_strlen(base);
    
    if (nb >= (unsigned long)base_len) {
        count += my_putnbr_unsigned_long_base(nb / base_len, base);
    }
    
    count += my_putchar(base[nb % base_len]);
    return count;
}

int my_strcmp(char *s1, char *s2)
{
    int i = 0;
    
    if (!s1 || !s2)
        return -1;
    
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    
    return s1[i] - s2[i];
}

char *my_strdup(char *src)
{
    char *dest;
    int len;
    int i = 0;
    
    if (!src)
        return NULL;
    
    len = my_strlen(src);
    dest = malloc(len + 1);
    
    if (!dest)
        return NULL;
    
    while (i <= len) {
        dest[i] = src[i];
        i++;
    }
    
    return dest;
}

void *my_memset(void *s, int c, int n)
{
    char *ptr = (char *)s;
    int i = 0;
    
    while (i < n) {
        ptr[i] = c;
        i++;
    }
    
    return s;
}
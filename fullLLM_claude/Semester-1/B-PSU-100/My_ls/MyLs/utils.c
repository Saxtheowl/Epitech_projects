#include "my_ls.h"

int my_strlen(char const *str)
{
    int len = 0;
    
    if (!str)
        return 0;
    
    while (str[len])
        len++;
    
    return len;
}

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;
    
    if (!s1 || !s2)
        return (!s1 && !s2) ? 0 : (!s1) ? -1 : 1;
    
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    
    return s1[i] - s2[i];
}

char *my_strdup(char const *str)
{
    int len = my_strlen(str);
    char *dup = malloc(len + 1);
    int i;
    
    if (!dup || !str)
        return 0;
    
    for (i = 0; i < len; i++)
        dup[i] = str[i];
    dup[i] = '\0';
    
    return dup;
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

char *my_strcat(char *dest, char const *src)
{
    int dest_len = my_strlen(dest);
    int i = 0;
    
    if (!dest || !src)
        return dest;
    
    while (src[i]) {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    
    return dest;
}

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char const *str)
{
    if (!str)
        return;
    
    write(1, str, my_strlen(str));
}

void my_put_nbr(int nb)
{
    if (nb == -2147483648) {
        my_putchar('-');
        my_putchar('2');
        my_put_nbr(147483648);
        return;
    }
    
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    
    if (nb >= 10) {
        my_put_nbr(nb / 10);
    }
    
    my_putchar('0' + nb % 10);
}
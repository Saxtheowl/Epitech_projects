#include <unistd.h>
#include "bistromatic.h"

void my_putstr(char const *str)
{
    int i = 0;
    
    if (!str)
        return;
    while (str[i])
        i++;
    write(1, str, i);
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

int my_atoi(char const *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;
    
    if (!str)
        return 0;
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

int char_to_int(char c, char const *base)
{
    int i = 0;
    
    while (base[i]) {
        if (base[i] == c)
            return i;
        i++;
    }
    return -1;
}

char int_to_char(int val, char const *base)
{
    int base_len = my_strlen(base);
    
    if (val < 0 || val >= base_len)
        return 0;
    return base[val];
}

char *remove_leading_zeros(char *nb, char const *base)
{
    int i = 0;
    int len = my_strlen(nb);
    
    if (!nb || len == 0)
        return nb;
    
    while (i < len - 1 && nb[i] == base[0])
        i++;
    
    if (i > 0) {
        int j = 0;
        while (i < len) {
            nb[j] = nb[i];
            i++;
            j++;
        }
        nb[j] = '\0';
    }
    return nb;
}

int is_negative(char const *nb, char const *base)
{
    if (!nb || my_strlen(nb) == 0)
        return 0;
    return (nb[0] == base[my_strlen(base) - 1]);
}

int compare_abs(char const *nb1, char const *nb2, char const *base)
{
    int len1 = my_strlen(nb1);
    int len2 = my_strlen(nb2);
    int i;
    
    if (len1 > len2)
        return 1;
    if (len1 < len2)
        return -1;
    
    for (i = 0; i < len1; i++) {
        int val1 = char_to_int(nb1[i], base);
        int val2 = char_to_int(nb2[i], base);
        if (val1 > val2)
            return 1;
        if (val1 < val2)
            return -1;
    }
    return 0;
}
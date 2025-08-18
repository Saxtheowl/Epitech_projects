#include <unistd.h>
#include <stdlib.h>
#include "infin_add.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char const *str)
{
    int i = 0;
    
    if (!str)
        return;
    while (str[i]) {
        my_putchar(str[i]);
        i++;
    }
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

char *my_strdup(char const *str)
{
    char *dup;
    int len = my_strlen(str);
    int i = 0;
    
    if (!str)
        return NULL;
    
    dup = malloc(len + 1);
    if (!dup)
        return NULL;
    
    while (i < len) {
        dup[i] = str[i];
        i++;
    }
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

int is_negative(char const *str)
{
    return (str && str[0] == '-');
}

char *remove_leading_zeros(char *str)
{
    int i = 0;
    int j = 0;
    int len = my_strlen(str);
    int has_minus = 0;
    
    if (!str || len == 0)
        return str;
    
    if (str[0] == '-') {
        has_minus = 1;
        i = 1;
    }
    
    while (i < len && str[i] == '0')
        i++;
    
    if (i == len) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    
    if (has_minus) {
        str[j++] = '-';
    }
    
    while (i < len) {
        str[j++] = str[i++];
    }
    str[j] = '\0';
    
    return str;
}

int compare_abs(char const *nb1, char const *nb2)
{
    int len1, len2;
    int start1 = 0, start2 = 0;
    int i;
    
    if (nb1[0] == '-')
        start1 = 1;
    if (nb2[0] == '-')
        start2 = 1;
    
    len1 = my_strlen(nb1 + start1);
    len2 = my_strlen(nb2 + start2);
    
    if (len1 > len2)
        return 1;
    if (len1 < len2)
        return -1;
    
    for (i = 0; i < len1; i++) {
        if (nb1[start1 + i] > nb2[start2 + i])
            return 1;
        if (nb1[start1 + i] < nb2[start2 + i])
            return -1;
    }
    
    return 0;
}
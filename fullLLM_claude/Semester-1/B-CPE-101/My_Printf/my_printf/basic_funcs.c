#include "my.h"

int my_putchar(char c)
{
    write(1, &c, 1);
    return 1;
}

int my_putstr(char *str)
{
    int count = 0;
    
    if (!str)
        return 0;
    
    while (str[count]) {
        my_putchar(str[count]);
        count++;
    }
    
    return count;
}

int my_putstr_non_printable(char *str)
{
    int count = 0;
    int i = 0;
    
    if (!str)
        return 0;
    
    while (str[i]) {
        if (str[i] >= ' ' && str[i] <= '~') {
            count += my_putchar(str[i]);
        } else {
            count += my_putchar('\\');
            if (str[i] < 8) {
                count += my_putchar('0');
                count += my_putchar('0');
                count += my_putchar('0' + str[i]);
            } else if (str[i] < 64) {
                count += my_putchar('0');
                count += my_putchar('0' + (str[i] / 8));
                count += my_putchar('0' + (str[i] % 8));
            } else {
                count += my_putchar('0' + (str[i] / 64));
                count += my_putchar('0' + ((str[i] % 64) / 8));
                count += my_putchar('0' + (str[i] % 8));
            }
        }
        i++;
    }
    
    return count;
}

int my_strlen(char *str)
{
    int len = 0;
    
    if (!str)
        return 0;
    
    while (str[len])
        len++;
    
    return len;
}

char *my_strcpy(char *dest, char *src)
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
#include <unistd.h>
#include <stdlib.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char const *str)
{
    if (!str)
        return;
    while (*str) {
        my_putchar(*str);
        str++;
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

int my_atoi(char const *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;
    
    if (!str)
        return 0;
    
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    
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
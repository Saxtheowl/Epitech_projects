#include <unistd.h>
#include "eval_expr.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_put_nbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        if (nb == -2147483648) {
            my_putchar('2');
            nb = -147483648;
        }
        nb = -nb;
    }
    if (nb >= 10) {
        my_put_nbr(nb / 10);
    }
    my_putchar(nb % 10 + '0');
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

void skip_spaces(char const *str, int *pos)
{
    while (str[*pos] == ' ' || str[*pos] == '\t')
        (*pos)++;
}

int my_getnbr(char const *str, int *pos)
{
    int result = 0;
    int sign = 1;
    
    skip_spaces(str, pos);
    
    if (str[*pos] == '-') {
        sign = -1;
        (*pos)++;
    } else if (str[*pos] == '+') {
        (*pos)++;
    }
    
    while (str[*pos] >= '0' && str[*pos] <= '9') {
        result = result * 10 + (str[*pos] - '0');
        (*pos)++;
    }
    
    return result * sign;
}
#include "my_navy.h"

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

int is_valid_coordinate(char const *coord)
{
    if (!coord || my_strlen(coord) != 2)
        return 0;
    
    if (coord[0] < 'A' || coord[0] > 'H')
        return 0;
    
    if (coord[1] < '1' || coord[1] > '8')
        return 0;
    
    return 1;
}

int parse_coordinate(char const *coord, int *x, int *y)
{
    if (!is_valid_coordinate(coord))
        return 0;
    
    *y = coord[0] - 'A';
    *x = coord[1] - '1';
    
    return 1;
}
/*
** EPITECH PROJECT, 2024
** FazzBizz
** File description:
** FizzBuzz variant with Fazz (10) and Bizz (9)
*/

#include <unistd.h>

int my_atoi(char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;
    
    if (str[i] == '-') {
        sign = -1;
        i++;
    }
    
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return result * sign;
}

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char *str)
{
    int i = 0;
    
    while (str[i]) {
        my_putchar(str[i]);
        i++;
    }
}

void my_puterr(char *str)
{
    int len = 0;
    
    while (str[len])
        len++;
    write(2, str, len);
}

void my_putnbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    
    if (nb >= 10) {
        my_putnbr(nb / 10);
    }
    
    my_putchar((nb % 10) + '0');
}

int main(int argc, char **argv)
{
    int start, end, i;
    
    if (argc != 3) {
        return 84;
    }
    
    start = my_atoi(argv[1]);
    end = my_atoi(argv[2]);
    
    if (end < start) {
        my_puterr("Error: the second parameter must be greater than the first one.\n");
        return 84;
    }
    
    for (i = start; i <= end; i++) {
        if (i % 10 == 0 && i % 9 == 0) {
            my_putstr("FazzBizz\n");
        } else if (i % 10 == 0) {
            my_putstr("Fazz\n");
        } else if (i % 9 == 0) {
            my_putstr("Bizz\n");
        } else {
            my_putnbr(i);
            my_putchar('\n');
        }
    }
    
    return 0;
}
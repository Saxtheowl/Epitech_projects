/*
** EPITECH PROJECT, 2024
** Day07 - B-CPE-100
** File description:
** my_putnbr.c
*/

void my_putchar(char c);

int my_putnbr(int nb)
{
    long num = nb;
    
    if (num < 0) {
        my_putchar('-');
        num = -num;
    }
    
    if (num >= 10) {
        my_putnbr(num / 10);
    }
    
    my_putchar((num % 10) + '0');
    return 0;
}
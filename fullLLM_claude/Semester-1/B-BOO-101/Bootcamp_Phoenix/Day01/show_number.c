/*
** EPITECH PROJECT, 2024
** show_number
** File description:
** Display the number given as a parameter
*/

int my_putchar(char c);

static void show_positive_number(int nb)
{
    if (nb >= 10)
        show_positive_number(nb / 10);
    my_putchar(nb % 10 + '0');
}

int show_number(int nb)
{
    if (nb == 0) {
        my_putchar('0');
        return 0;
    }
    if (nb < 0) {
        my_putchar('-');
        if (nb == -2147483648) {
            my_putchar('2');
            show_positive_number(147483648);
        } else {
            show_positive_number(-nb);
        }
    } else {
        show_positive_number(nb);
    }
    return 0;
}
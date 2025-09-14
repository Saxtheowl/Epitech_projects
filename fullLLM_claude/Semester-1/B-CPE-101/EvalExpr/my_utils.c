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
            my_put_nbr(-(nb / 10));
            my_putchar('8');
            return;
        }
        nb = -nb;
    }
    
    if (nb >= 10) {
        my_put_nbr(nb / 10);
    }
    
    my_putchar('0' + (nb % 10));
}
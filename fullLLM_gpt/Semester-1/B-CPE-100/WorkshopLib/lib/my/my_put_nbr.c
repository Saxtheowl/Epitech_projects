#include "my.h"

int my_put_nbr(int nb)
{
    long value = nb;
    int count = 0;

    if (value < 0) {
        my_putchar('-');
        count += 1;
        value = -value;
    }
    if (value >= 10) {
        count += my_put_nbr((int)(value / 10));
    }
    my_putchar((char)('0' + (value % 10)));
    return count + 1;
}

#include "phoenix.h"

int show_number(int nb)
{
    long value = nb;

    if (value < 0) {
        my_putchar('-');
        value = -value;
    }
    if (value >= 10) {
        show_number((int)(value / 10));
    }
    my_putchar((char)('0' + (value % 10)));
    return 0;
}

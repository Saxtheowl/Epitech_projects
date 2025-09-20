#include <unistd.h>
#include <stddef.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(const char *str)
{
    if (!str)
        return;
    while (*str) {
        write(1, str, 1);
        ++str;
    }
}

static void my_putnbr_unsigned_rec(size_t nb)
{
    if (nb >= 10)
        my_putnbr_unsigned_rec(nb / 10);
    my_putchar((char)('0' + (nb % 10)));
}

void my_putnbr_unsigned(size_t nb)
{
    my_putnbr_unsigned_rec(nb);
}

static void my_putnbr_rec(long nb)
{
    if (nb >= 10)
        my_putnbr_rec(nb / 10);
    my_putchar((char)('0' + (nb % 10)));
}

void my_putnbr(int nb)
{
    long value = nb;

    if (value < 0) {
        my_putchar('-');
        value = -value;
    }
    my_putnbr_rec(value);
}

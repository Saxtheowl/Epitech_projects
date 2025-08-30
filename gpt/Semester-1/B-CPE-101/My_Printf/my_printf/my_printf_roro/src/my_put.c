/*
** EPITECH PROJECT, 2025
** my_printf_roro
** File description:
** Basic output helpers
*/

#include <unistd.h>
#include <stddef.h>

int my_putc(char c)
{
    return (int)write(1, &c, 1);
}

int my_puts(const char *s)
{
    size_t n;

    if (!s)
        s = "(null)";
    for (n = 0; s[n]; ++n)
        ;
    return (int)write(1, s, n);
}

static int my_putnbr_rec(long v)
{
    char c;
    int n;

    if (v >= 10)
        n = my_putnbr_rec(v / 10);
    else
        n = 0;
    c = (char)('0' + (v % 10));
    my_putc(c);
    return n + 1;
}

int my_putnbr(long v)
{
    int n;

    if (v < 0) {
        my_putc('-');
        n = 1 + my_putnbr_rec(-v);
    } else {
        n = my_putnbr_rec(v);
    }
    return n;
}

static int my_putun_rec(unsigned long v)
{
    char c;
    int n;

    if (v >= 10)
        n = my_putun_rec(v / 10);
    else
        n = 0;
    c = (char)('0' + (v % 10));
    my_putc(c);
    return n + 1;
}

int my_putun(unsigned long v)
{
    return my_putun_rec(v);
}

int my_putbase(unsigned long v, const char *digits)
{
    char buf[65];
    int i;
    int b;
    int n;

    b = 0;
    while (digits[b])
        b += 1;
    if (b < 2)
        b = 10;
    if (v == 0) {
        my_putc('0');
        return 1;
    }
    i = 0;
    while (v > 0 && i < 64) {
        buf[i++] = digits[v % (unsigned)b];
        v /= (unsigned)b;
    }
    n = i;
    while (i-- > 0)
        my_putc(buf[i]);
    return n;
}

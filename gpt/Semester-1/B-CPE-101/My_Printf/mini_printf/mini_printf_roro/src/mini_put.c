/*
** EPITECH PROJECT, 2025
** mini_printf_roro
** File description:
** Basic output
*/

#include <unistd.h>
#include <stddef.h>

int mp_putc(char c)
{
    return (int)write(1, &c, 1);
}

int mp_puts(const char *s)
{
    size_t n;

    if (!s)
        s = "(null)";
    for (n = 0; s[n]; ++n)
        ;
    return (int)write(1, s, n);
}

static int mp_putnbr_rec(long v)
{
    char c;
    int n;

    if (v >= 10)
        n = mp_putnbr_rec(v / 10);
    else
        n = 0;
    c = (char)('0' + (v % 10));
    mp_putc(c);
    return n + 1;
}

int mp_putnbr(long v)
{
    int n;

    if (v < 0) {
        mp_putc('-');
        n = 1 + mp_putnbr_rec(-v);
    } else {
        n = mp_putnbr_rec(v);
    }
    return n;
}

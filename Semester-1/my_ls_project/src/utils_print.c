/*
** EPITECH PROJECT, 2025
** MY_LS
** File description:
** Epitech-style source file for my_ls project
*/
#include "my_ls.h"
#include <unistd.h>

void my_write_char(int fd, char c)
{
    write(fd, &c, 1);
}

void my_write_str(int fd, const char *s)
{
    if (!s)
        return;
    write(fd, s, my_strlen(s));
}

static void write_rev(int fd, char *buf, int i, int neg)
{
    int start = 0;

    if (neg) {
        my_write_char(fd, '-');
    }
    while (i > start) {
        char t = buf[start];

        buf[start] = buf[i];
        buf[i] = t;
        start++;
        i--;
    }
    write(fd, buf, my_strlen(buf));
}

void my_write_ll(int fd, long long n)
{
    char buf[32];
    int i = 0;
    int neg = 0;
    long long m = n;

    if (m == 0) {
        my_write_char(fd, '0');
        return;
    }
    if (m < 0) {
        neg = 1;
        m = -m;
    }
    while (m > 0 && i < (int)(sizeof(buf) - 1)) {
        buf[i++] = (char)('0' + (m % 10));
        m /= 10;
    }
    buf[i] = '\0';
    write_rev(fd, buf, i - 1, neg);
}

void my_write_sz(int fd, size_t n)
{
    my_write_ll(fd, (long long)n);
}

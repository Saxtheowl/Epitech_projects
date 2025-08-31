/*
** EPITECH PROJECT, 2025
** Trade
** File description:
**   Simple I/O utils
*/

#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include "trade.h"

int io_read_line(int fd, char *buf, size_t cap)
{
    size_t i = 0;
    char c = 0;
    ssize_t r = 0;

    if (!buf || cap == 0)
        return -1;
    while (i + 1 < cap) {
        r = read(fd, &c, 1);
        if (r <= 0)
            break;
        if (c == '\n')
            break;
        buf[i++] = c;
    }
    buf[i] = '\0';
    return (int)i;
}

void io_write(const char *s)
{
    if (!s)
        return;
    write(1, s, strlen(s));
}

void io_writef(const char *fmt, const char *a, const char *b)
{
    char buf[512];
    size_t ia = 0;
    size_t ib = 0;
    size_t k = 0;

    (void)b;
    for (k = 0; fmt[k] && k < sizeof(buf) - 1; ++k)
        buf[k] = fmt[k];
    buf[k] = '\0';
    io_write(buf);
    (void)a;
}


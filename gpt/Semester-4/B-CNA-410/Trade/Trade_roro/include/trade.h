/*
** EPITECH PROJECT, 2025
** Trade
** File description:
**   Bot interfaces
*/

#ifndef TRADE_H
#define TRADE_H

#include <stddef.h>

int io_read_line(int fd, char *buf, size_t cap);
void io_write(const char *s);
void io_writef(const char *fmt, const char *a, const char *b);

void bot_loop(void);

#endif /* TRADE_H */


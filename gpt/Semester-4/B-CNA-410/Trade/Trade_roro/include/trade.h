/*
** EPITECH PROJECT, 2025
** Trade
** File description:
**   Bot interfaces
*/

#ifndef TRADE_H
#define TRADE_H

#include <stddef.h>

typedef struct candle_s {
    long time;
    double open;
    double high;
    double low;
    double close;
    double volume;
} candle_t;

typedef struct market_s {
    char pair[64];
    candle_t buf[256];
    size_t count;
} market_t;

typedef struct settings_s {
    int timebank;
    int time_per_move;
    int candle_interval;
    int candle_count;
    double initial_stack;
    double fee_percent;
    char candle_format[64];
    char your_bot[64];
    double stack_eth;
    double stack_btc;
    double stack_usdt;
} settings_t;

int io_read_line(int fd, char *buf, size_t cap);
void io_write(const char *s);
void io_writef(const char *fmt, const char *a, const char *b);

void bot_loop(void);

/* parsing */
void settings_init(settings_t *st);
void market_init(market_t *m);
int parse_settings_line(settings_t *st, const char *line);
int parse_next_candles(market_t *m, const char *payload);
int parse_candle_line(market_t *m, const char *payload);
int handle_action(const settings_t *st, const market_t *m);
int parse_stacks_line(settings_t *st, const char *payload);

#endif /* TRADE_H */

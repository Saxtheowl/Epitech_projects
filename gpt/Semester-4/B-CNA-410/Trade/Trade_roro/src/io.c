/*
** EPITECH PROJECT, 2025
** Trade
** File description:
**   Simple I/O utils
*/

#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "trade.h"
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
    (void)ib;
    buf[0] = '\0';
    for (k = 0; fmt[k] && k < sizeof(buf) - 1; ++k) {
        if (fmt[k] == '%' && fmt[k + 1] == 's') {
            const char *src = (ia == 0) ? a : b;
            size_t j = 0;
            ia += 1;
            k += 1;
            while (src && src[j] && j + 1 < sizeof(buf)) {
                size_t len = strlen(buf);
                if (len + 1 >= sizeof(buf))
                    break;
                buf[len] = src[j];
                buf[len + 1] = '\0';
                j += 1;
            }
        } else {
            size_t len = strlen(buf);
            buf[len] = fmt[k];
            buf[len + 1] = '\0';
        }
    }
    buf[sizeof(buf) - 1] = '\0';
    io_write(buf);
}

static long to_long(const char *s)
{
    char *e = NULL;
    long v = strtol(s, &e, 10);
    (void)e;
    return v;
}

static double to_double(const char *s)
{
    char *e = NULL;
    double v = strtod(s, &e);
    (void)e;
    return v;
}

void settings_init(settings_t *st)
{
    memset(st, 0, sizeof(*st));
}

void market_init(market_t *m)
{
    memset(m, 0, sizeof(*m));
}

static void copy_kv(char *dst, size_t cap, const char *src)
{
    size_t n = strlen(src);

    if (n >= cap)
        n = cap - 1;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

int parse_settings_line(settings_t *st, const char *line)
{
    /* expects: key value or key=value */
    const char *eq = strchr(line, '=');
    if (eq) {
        size_t klen = (size_t)(eq - line);
        char key[64];
        const char *val = eq + 1;
        if (klen >= sizeof(key)) klen = sizeof(key) - 1;
        memcpy(key, line, klen);
        key[klen] = '\0';
        if (strcmp(key, "timebank") == 0) st->timebank = (int)to_long(val);
        else if (strcmp(key, "time_per_move") == 0) st->time_per_move = (int)to_long(val);
        else if (strcmp(key, "candle_interval") == 0) st->candle_interval = (int)to_long(val);
        else if (strcmp(key, "candle_count") == 0) st->candle_count = (int)to_long(val);
        else if (strcmp(key, "initial_stack") == 0) st->initial_stack = to_double(val);
        else if (strcmp(key, "transaction_fee_percent") == 0) st->fee_percent = to_double(val);
        else if (strcmp(key, "candle_format") == 0) copy_kv(st->candle_format, sizeof(st->candle_format), val);
        else if (strcmp(key, "your_bot") == 0) copy_kv(st->your_bot, sizeof(st->your_bot), val);
        return 0;
    }
    return -1;
}

static int parse_one_candle(candle_t *c, const char *s)
{
    /* format: time,open,high,low,close,volume */
    char tmp[128];
    char *tok;
    int i;

    copy_kv(tmp, sizeof(tmp), s);
    tok = strtok(tmp, ",");
    for (i = 0; i < 6 && tok; ++i) {
        switch (i) {
        case 0: c->time = to_long(tok); break;
        case 1: c->open = to_double(tok); break;
        case 2: c->high = to_double(tok); break;
        case 3: c->low = to_double(tok); break;
        case 4: c->close = to_double(tok); break;
        case 5: c->volume = to_double(tok); break;
        }
        tok = strtok(NULL, ",");
    }
    return (i == 6) ? 0 : -1;
}

int parse_next_candles(market_t *m, const char *payload)
{
    /* Grammar variant A (from PDF):
     *   PAIR,time,open,high,low,close,volume;PAIR,...;PAIR,...
     * Variant B (legacy):
     *   PAIR;time,open,high,low,close,volume|time,open,...
     * We will support A and fallback to B.
     */
    char buf[1024];
    char *seg;
    size_t handled = 0;

    copy_kv(buf, sizeof(buf), payload);
    /* Try variant A: segments separated by ';' each starting with PAIR, */
    seg = strtok(buf, ";");
    while (seg) {
        char *comma = strchr(seg, ',');
        if (comma) {
            char pair[64];
            size_t n = (size_t)(comma - seg);
            if (n >= sizeof(pair)) n = sizeof(pair) - 1;
            memcpy(pair, seg, n);
            pair[n] = '\0';
            copy_kv(m->pair, sizeof(m->pair), pair);
            /* parse one candle from the rest of this segment */
            if (m->count < sizeof(m->buf)/sizeof(m->buf[0])) {
                if (parse_one_candle(&m->buf[m->count], comma + 1) == 0)
                    m->count += 1, handled += 1;
            }
        }
        seg = strtok(NULL, ";");
    }
    if (handled > 0)
        return 0;
    /* Fallback variant B */
    {
        char b2[1024];
        char *p;
        char *item;
        size_t idx = 0;
        copy_kv(b2, sizeof(b2), payload);
        p = strchr(b2, ';');
        if (!p)
            return -1;
        *p = '\0';
        copy_kv(m->pair, sizeof(m->pair), b2);
        item = strtok(p + 1, "|");
        while (item && idx < sizeof(m->buf) / sizeof(m->buf[0])) {
            if (parse_one_candle(&m->buf[idx], item) == 0)
                idx += 1;
            item = strtok(NULL, "|");
        }
        m->count = idx;
        return 0;
    }
}

int parse_candle_line(market_t *m, const char *payload)
{
    /* payload: PAIR <time,open,high,low,close,volume> */
    char buf[256];
    const char *sp;
    candle_t c;

    copy_kv(buf, sizeof(buf), payload);
    sp = strchr(buf, ' ');
    if (!sp)
        return -1;
    * (char *)sp = '\0';
    copy_kv(m->pair, sizeof(m->pair), buf);
    if (parse_one_candle(&c, sp + 1) != 0)
        return -1;
    if (m->count < sizeof(m->buf) / sizeof(m->buf[0])) {
        m->buf[m->count++] = c;
    } else {
        size_t i;
        for (i = 1; i < m->count; ++i)
            m->buf[i - 1] = m->buf[i];
        m->buf[m->count - 1] = c;
    }
    return 0;
}

int parse_stacks_line(settings_t *st, const char *payload)
{
    /* payload: ETH:val,BTC:val,USDT:val */
    char buf[128];
    char *tok;
    copy_kv(buf, sizeof(buf), payload);
    tok = strtok(buf, ",");
    while (tok) {
        char *kv = strchr(tok, ':');
        if (kv) {
            *kv = '\0';
            if (strcmp(tok, "ETH") == 0) st->stack_eth = to_double(kv + 1);
            else if (strcmp(tok, "BTC") == 0) st->stack_btc = to_double(kv + 1);
            else if (strcmp(tok, "USDT") == 0) st->stack_usdt = to_double(kv + 1);
        }
        tok = strtok(NULL, ",");
    }
    return 0;
}

static double sma_close(const market_t *m, size_t n)
{
    size_t i;
    double s = 0.0;
    if (m->count < n || n == 0)
        return 0.0;
    for (i = m->count - n; i < m->count; ++i)
        s += m->buf[i].close;
    return s / (double)n;
}

static int split_pair(const char *pair, char *base, size_t cbase, char *quote,
    size_t cquote)
{
    const char *u = strchr(pair, '_');
    size_t nb;
    if (!u)
        return -1;
    nb = (size_t)(u - pair);
    if (nb >= cbase) nb = cbase - 1;
    memcpy(base, pair, nb);
    base[nb] = '\0';
    strncpy(quote, u + 1, cquote - 1);
    quote[cquote - 1] = '\0';
    return 0;
}

static double *stack_ptr(settings_t *st, const char *cur)
{
    if (strcmp(cur, "ETH") == 0) return &st->stack_eth;
    if (strcmp(cur, "BTC") == 0) return &st->stack_btc;
    if (strcmp(cur, "USDT") == 0) return &st->stack_usdt;
    return NULL;
}

int handle_action(const settings_t *st, const market_t *m)
{
    char base[8];
    char quote[8];
    double last;
    double prev;
    double fee;
    double *qstk;
    double *bstk;

    if (m->count < 2) {
        io_write("pass\n");
        return 0;
    }
    last = m->buf[m->count - 1].close;
    prev = m->buf[m->count - 2].close;
    fee = st->fee_percent; /* percent, e.g., 0.1 */
    if (split_pair(m->pair, base, sizeof(base), quote, sizeof(quote)) != 0) {
        io_write("pass\n");
        return 0;
    }
    qstk = stack_ptr((settings_t *)st, quote);
    bstk = stack_ptr((settings_t *)st, base);
    if (!qstk || !bstk) {
        io_write("pass\n");
        return 0;
    }
    if (last > prev) {
        double cost = last * 1.0 * (1.0 + fee / 100.0);
        if (*qstk >= cost) {
            io_writef("buy %s 1\n", m->pair, NULL);
            return 0;
        }
        io_write("pass\n");
        return 0;
    }
    if (last < prev) {
        if (*bstk >= 1.0) {
            io_writef("sell %s 1\n", m->pair, NULL);
            return 0;
        }
        io_write("pass\n");
        return 0;
    }
    io_write("pass\n");
    return 0;
}

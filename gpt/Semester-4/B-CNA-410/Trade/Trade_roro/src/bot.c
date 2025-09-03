/*
** EPITECH PROJECT, 2025
** Trade
** File description:
**   Minimal bot: always pass
*/

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "trade.h"

static int starts_with(const char *s, const char *p)
{
    size_t i = 0;
    for (i = 0; p[i]; ++i)
        if (s[i] != p[i])
            return 0;
    return 1;
}

static const char *skip_space(const char *s)
{
    while (*s == ' ' || *s == '\t')
        ++s;
    return s;
}

static int split3(const char *s, char *a, size_t ca, char *b, size_t cb)
{
    const char *p = strchr(s, ' ');
    size_t n;

    if (!p)
        return -1;
    n = (size_t)(p - s);
    if (n >= ca)
        n = ca - 1;
    memcpy(a, s, n);
    a[n] = '\0';
    s = skip_space(p + 1);
    n = strlen(s);
    if (n >= cb)
        n = cb - 1;
    memcpy(b, s, n);
    b[n] = '\0';
    return 0;
}

static void process_line(settings_t *st, market_t *m, const char *line)
{
    if (starts_with(line, "settings ")) {
        parse_settings_line(st, line + 9);
        return;
    }
    if (starts_with(line, "update game next_candles ")) {
        const char *p = strchr(line, ' ');
        if (!p) return;
        p = strchr(p + 1, ' ');
        if (!p) return;
        p = strchr(p + 1, ' ');
        if (!p) return;
        p = skip_space(p + 1);
        parse_next_candles(m, p);
        return;
    }
    if (starts_with(line, "update game candle ")) {
        const char *p = strchr(line, ' ');
        if (!p) return;
        p = strchr(p + 1, ' ');
        if (!p) return;
        p = strchr(p + 1, ' ');
        if (!p) return;
        p = skip_space(p + 1);
        parse_candle_line(m, p);
        return;
    }
    if (starts_with(line, "update game stacks ")) {
        const char *p = strchr(line, ' ');
        if (!p) return;
        p = strchr(p + 1, ' ');
        if (!p) return;
        p = strchr(p + 1, ' ');
        if (!p) return;
        p = skip_space(p + 1);
        parse_stacks_line(st, p);
        return;
    }
    if (starts_with(line, "action order")) {
        (void)handle_action(st, m);
        return;
    }
}

void bot_loop(void)
{
    char line[1024];
    settings_t st;
    market_t m;

    settings_init(&st);
    market_init(&m);
    while (1) {
        int r = io_read_line(0, line, sizeof(line));
        if (r <= 0)
            break;
        process_line(&st, &m, line);
    }
}

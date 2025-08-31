/*
** EPITECH PROJECT, 2025
** Trade
** File description:
**   Minimal bot: always pass
*/

#include <string.h>
#include "trade.h"

static int starts_with(const char *s, const char *p)
{
    size_t i = 0;
    for (i = 0; p[i]; ++i) {
        if (s[i] != p[i])
            return 0;
    }
    return 1;
}

void bot_loop(void)
{
    char line[1024];

    while (1) {
        int r = io_read_line(0, line, sizeof(line));
        if (r <= 0)
            break;
        if (starts_with(line, "action")) {
            io_write("pass\n");
        } else {
            /* ignore settings/update */
        }
    }
}


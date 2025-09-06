/*
** EPITECH PROJECT, 2025
** Gomoku_roro
** File description:
**   Protocol parser (Gomocup-like)
*/

#include <stdio.h>
#include <string.h>
#include "gomoku.h"

static int cmd_start(gomoku_t *g, const char *arg)
{
    int n;

    if (parse_int(arg, &n) != 0 || n <= 0)
        { printf("ERROR\n"); return 0; }
    board_free(g);
    if (board_init(g, n) != 0)
        { printf("ERROR\n"); return 0; }
    printf("OK\n");
    return 0;
}

static int reply_move(gomoku_t *g)
{
    int x;
    int y;

    ai_pick_move(g, &x, &y);
    board_set(g, x, y, 1);
    printf("%d,%d\n", x, y);
    return 0;
}

static int cmd_turn(gomoku_t *g, const char *arg)
{
    char l[32];
    char r[32];
    int x, y;

    if (split_at(arg, ',', l, sizeof l, r, sizeof r) != 0)
        { printf("ERROR\n"); return 0; }
    if (parse_int(l, &x) != 0 || parse_int(r, &y) != 0)
        { printf("ERROR\n"); return 0; }
    board_set(g, x, y, 2);
    return reply_move(g);
}

static int cmd_begin(gomoku_t *g)
{
    return reply_move(g);
}

static int cmd_board(gomoku_t *g)
{
    char buf[128];
    char *line;
    char a[32], b[32], c[32];
    int x, y, who;

    while (fgets(buf, sizeof buf, stdin)) {
        line = str_trim(buf);
        if (strcmp(line, "DONE") == 0)
            break;
        if (sscanf(line, "%31[^,],%31[^,],%31s", a, b, c) == 3) {
            if (parse_int(a, &x) == 0 && parse_int(b, &y) == 0
                && parse_int(c, &who) == 0)
                board_set(g, x, y, who == 1 ? 1 : 2);
        }
    }
    return reply_move(g);
}

static int cmd_about(void)
{
    printf("name=\"gomoku_roro\", version=\"1.0\", author=\"roro\", country=\"FR\"\n");
    return 0;
}

static int cmd_takeback(gomoku_t *g, const char *arg)
{
    char l[32];
    char r[32];
    int x, y;

    if (split_at(arg, ',', l, sizeof l, r, sizeof r) != 0)
        { printf("ERROR\n"); return 0; }
    if (parse_int(l, &x) != 0 || parse_int(r, &y) != 0)
        { printf("ERROR\n"); return 0; }
    if (board_in_bounds(g, x, y))
        board_set(g, x, y, 0);
    printf("OK\n");
    return 0;
}

int handle_line(gomoku_t *g, const char *line)
{
    char cmd[32];
    const char *arg;

    line = str_trim((char *)line);
    if (sscanf(line, "%31s", cmd) != 1)
        return 0;
    arg = line + strlen(cmd);
    while (*arg == ' ')
        arg++;
    if (strcmp(cmd, "START") == 0)
        return cmd_start(g, arg);
    if (strcmp(cmd, "TURN") == 0)
        return cmd_turn(g, arg);
    if (strcmp(cmd, "BEGIN") == 0)
        return cmd_begin(g);
    if (strcmp(cmd, "BOARD") == 0)
        return cmd_board(g);
    if (strcmp(cmd, "ABOUT") == 0)
        return cmd_about();
    if (strcmp(cmd, "INFO") == 0)
        return 0;
    if (strcmp(cmd, "TAKEBACK") == 0)
        return cmd_takeback(g, arg);
    if (strcmp(cmd, "END") == 0)
        return 1;
    printf("UNKNOWN\n");
    return 0;
}


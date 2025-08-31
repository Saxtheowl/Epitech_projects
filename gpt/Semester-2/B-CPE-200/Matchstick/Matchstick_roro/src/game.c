/*
** EPITECH PROJECT, 2025
** Matchstick
** File description:
** Game loop and turns
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "matchstick.h"

static int parse_number(const char *s, int *out)
{
    long v;
    int i;

    if (!s || *s == '\0')
        return 0;
    i = 0;
    while (s[i] != '\0') {
        if (!isdigit((unsigned char)s[i]))
            return 0;
        i = i + 1;
    }
    v = strtol(s, NULL, 10);
    if (v < 0 || v > 1000000)
        return 0;
    *out = (int)v;
    return 1;
}

int parse_args(int argc, char **argv, int *lines, int *max_remove)
{
    int l;
    int m;

    if (argc != 3)
        return 0;
    if (!parse_number(argv[1], &l) || !parse_number(argv[2], &m))
        return 0;
    if (l < 1 || l > 99 || m < 1)
        return 0;
    *lines = l;
    *max_remove = m;
    return 1;
}

int player_turn(board_t *b)
{
    char *line;
    size_t cap;
    int ln;
    int rm;

    puts("Your turn:");
    line = NULL;
    cap = 0;
    fputs("Line: ", stdout);
    if (getline(&line, &cap, stdin) == -1) {
        free(line);
        return -1;
    }
    if (line[0] != '\0' && line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';
    if (!parse_number(line, &ln) || ln < 1 || ln > b->lines) {
        puts("Error: invalid input");
        free(line);
        return 0;
    }
    free(line);
    line = NULL;
    cap = 0;
    fputs("Matches: ", stdout);
    if (getline(&line, &cap, stdin) == -1) {
        free(line);
        return -1;
    }
    if (line[0] != '\0' && line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';
    if (!parse_number(line, &rm) || rm <= 0) {
        puts("Error: invalid input");
        free(line);
        return 0;
    }
    free(line);
    if (!remove_matches(b, ln, rm)) {
        puts("Error: not enough matches or exceeds limit");
        return 0;
    }
    printf("Player removed %d match(es) from line %d\n", rm, ln);
    return 1;
}

int ai_turn(board_t *b)
{
    int line;
    int rm;

    puts("AI's turn...");
    line = 1;
    while (line <= b->lines && count_line_matches(b, line) == 0)
        line = line + 1;
    if (line > b->lines)
        return 1;
    rm = count_line_matches(b, line);
    if (rm > b->max_remove)
        rm = b->max_remove;
    remove_matches(b, line, rm);
    printf("AI removed %d match(es) from line %d\n", rm, line);
    return 1;
}


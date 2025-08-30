/*
** EPITECH PROJECT, 2025
** MatchNmatch_roro
** File description:
** match and nmatch implementations
*/

#include <stddef.h>
#include "matchnmatch.h"

static int char_eq(char a, char b)
{
    return a == b;
}

int match(const char *s, const char *p)
{
    if (s == NULL || p == NULL)
        return 0;
    if (*p == '\0')
        return *s == '\0';
    if (*p == '*') {
        if (match(s, p + 1))
            return 1;
        return (*s != '\0') && match(s + 1, p);
    }
    if (*s == '\0')
        return 0;
    if (char_eq(*s, *p))
        return match(s + 1, p + 1);
    return 0;
}

static int nmatch_rec(const char *s, const char *p)
{
    if (*p == '\0')
        return (*s == '\0') ? 1 : 0;
    if (*p == '*') {
        if (*s == '\0')
            return nmatch_rec(s, p + 1);
        return nmatch_rec(s, p + 1) + nmatch_rec(s + 1, p);
    }
    if (*s == '\0')
        return 0;
    if (char_eq(*s, *p))
        return nmatch_rec(s + 1, p + 1);
    return 0;
}

int nmatch(const char *s, const char *p)
{
    if (s == NULL || p == NULL)
        return 0;
    return nmatch_rec(s, p);
}

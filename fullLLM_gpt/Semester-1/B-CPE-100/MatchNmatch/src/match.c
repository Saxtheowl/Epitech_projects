#include <stdio.h>
#include "matchnmatch.h"

static int match_rec(const char *s, const char *p)
{
    if (*p == '\0')
        return *s == '\0';
    if (*p == '*') {
        return match_rec(s, p + 1) || (*s && match_rec(s + 1, p));
    }
    if (*s == '\0')
        return 0;
    if (*p == *s)
        return match_rec(s + 1, p + 1);
    return 0;
}

int match(const char *s, const char *p)
{
    return match_rec(s, p) ? 1 : 0;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Usage: %s src pattern\n", argv[0]);
        return 84;
    }
    int r = match(argv[1], argv[2]);
    printf("match(\"%s\", \"%s\") returned %d\n", argv[1], argv[2], r);
    return 0;
}

#include <stdio.h>
#include "matchnmatch.h"

static int nmatch_rec(const char *s, const char *p)
{
    if (*p == '\0')
        return *s == '\0' ? 1 : 0;
    if (*p == '*') {
        int count = 0;
        count += nmatch_rec(s, p + 1);
        if (*s)
            count += nmatch_rec(s + 1, p);
        return count;
    }
    if (*s == '\0' || *p != *s)
        return 0;
    return nmatch_rec(s + 1, p + 1);
}

int nmatch(const char *s, const char *p)
{
    return nmatch_rec(s, p);
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Usage: %s src pattern\n", argv[0]);
        return 84;
    }
    int r = nmatch(argv[1], argv[2]);
    printf("nmatch(\"%s\", \"%s\") returned %d\n", argv[1], argv[2], r);
    return 0;
}

#include "matchnmatch.h"

static int match_rec(const char *s1, const char *s2)
{
    if (*s2 == '\0')
        return (*s1 == '\0');
    if (*s2 == '*') {
        if (match_rec(s1, s2 + 1))
            return 1;
        return (*s1 != '\0' && match_rec(s1 + 1, s2));
    }
    if (*s1 == '\0' || *s1 != *s2)
        return 0;
    return match_rec(s1 + 1, s2 + 1);
}

int match(const char *s1, const char *s2)
{
    if (s1 == 0 || s2 == 0)
        return 0;
    return match_rec(s1, s2) ? 1 : 0;
}

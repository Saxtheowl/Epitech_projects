#include "matchnmatch.h"

static int nmatch_rec(const char *s1, const char *s2)
{
    if (*s2 == '\0')
        return (*s1 == '\0') ? 1 : 0;
    if (*s2 == '*') {
        int count = nmatch_rec(s1, s2 + 1);
        if (*s1 != '\0')
            count += nmatch_rec(s1 + 1, s2);
        return count;
    }
    if (*s1 == '\0' || *s1 != *s2)
        return 0;
    return nmatch_rec(s1 + 1, s2 + 1);
}

int nmatch(const char *s1, const char *s2)
{
    if (s1 == 0 || s2 == 0)
        return 0;
    return nmatch_rec(s1, s2);
}

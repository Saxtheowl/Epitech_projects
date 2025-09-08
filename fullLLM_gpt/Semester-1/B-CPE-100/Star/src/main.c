#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "star.h"

static int parse_positive_int(const char *s, int *out)
{
    if (!s || !*s)
        return -1;
    long val = 0;
    for (const char *p = s; *p; ++p) {
        if (!isdigit((unsigned char)*p))
            return -1;
        val = val * 10 + (*p - '0');
        if (val > 1000000)
            return -1;
    }
    if (val <= 0)
        return -1;
    *out = (int)val;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        return 84;
    }
    int n = 0;
    if (parse_positive_int(argv[1], &n) != 0) {
        return 84;
    }
    print_star(n);
    return 0;
}

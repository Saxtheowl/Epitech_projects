#include <stddef.h>

#include "tree.h"

static int parse_size(const char *s, int *out)
{
    if (s == NULL || *s == '\0') {
        return -1;
    }

    long value = 0;

    for (const char *p = s; *p; ++p) {
        if (*p < '0' || *p > '9') {
            return -1;
        }
        value = value * 10 + (*p - '0');
        if (value > 1000000L) {
            return -1;
        }
    }

    *out = (int)value;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        return 84;
    }

    int size = 0;

    if (parse_size(argv[1], &size) != 0) {
        return 84;
    }

    tree(size);
    return 0;
}

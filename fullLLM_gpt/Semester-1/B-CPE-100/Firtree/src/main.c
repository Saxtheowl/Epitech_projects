#include <ctype.h>
#include <stdlib.h>

#include "tree.h"

static int parse_size(const char *s, unsigned int *out)
{
    if (s == NULL || *s == '\0') {
        return -1;
    }

    unsigned long value = 0;

    for (const unsigned char *p = (const unsigned char *)s; *p; ++p) {
        if (!isdigit(*p)) {
            return -1;
        }
        value = (value * 10UL) + (unsigned long)(*p - '0');
        if (value > 1000000UL) {
            return -1;
        }
    }

    *out = (unsigned int)value;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        return 84;
    }

    unsigned int size = 0;

    if (parse_size(argv[1], &size) != 0) {
        return 84;
    }

    tree((int)size);
    return 0;
}

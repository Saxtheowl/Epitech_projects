#include "phoenix.h"

static int string_length(char const *str)
{
    int length = 0;

    if (!str) {
        return 0;
    }
    while (str[length] != '\0') {
        ++length;
    }
    return length;
}

char *concat_strings(char *dest, char const *src)
{
    int dest_len = string_length(dest);
    int i = 0;

    if (!dest || !src) {
        return dest;
    }
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        ++i;
    }
    dest[dest_len + i] = '\0';
    return dest;
}

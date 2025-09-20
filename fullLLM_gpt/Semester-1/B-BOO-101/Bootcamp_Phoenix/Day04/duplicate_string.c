#include <stdlib.h>
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

char *duplicate_string(char const *src)
{
    int length = string_length(src);
    char *copy = malloc((length + 1) * sizeof(char));

    if (!copy) {
        return NULL;
    }
    for (int i = 0; i < length; ++i) {
        copy[i] = src[i];
    }
    copy[length] = '\0';
    return copy;
}

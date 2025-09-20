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

char *reverse_string(char *str)
{
    int length = string_length(str);

    if (!str) {
        return NULL;
    }
    for (int i = 0; i < length / 2; ++i) {
        char tmp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = tmp;
    }
    return str;
}

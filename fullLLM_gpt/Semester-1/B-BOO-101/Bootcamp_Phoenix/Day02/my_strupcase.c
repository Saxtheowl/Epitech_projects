#include "phoenix.h"

static int is_lower(char c)
{
    return c >= 'a' && c <= 'z';
}

char *my_strupcase(char *str)
{
    if (!str) {
        return NULL;
    }
    for (int i = 0; str[i] != '\0'; ++i) {
        if (is_lower(str[i])) {
            str[i] = (char)(str[i] - ('a' - 'A'));
        }
    }
    return str;
}

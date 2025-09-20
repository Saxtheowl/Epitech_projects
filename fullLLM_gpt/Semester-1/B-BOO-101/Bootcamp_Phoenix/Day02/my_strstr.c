#include "phoenix.h"

static int starts_with(char *str, char const *to_find)
{
    int i = 0;

    while (to_find[i] != '\0') {
        if (str[i] != to_find[i]) {
            return 0;
        }
        ++i;
    }
    return 1;
}

char *my_strstr(char *str, char const *to_find)
{
    if (!str || !to_find) {
        return NULL;
    }
    if (to_find[0] == '\0') {
        return str;
    }
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == to_find[0] && starts_with(&str[i], to_find)) {
            return &str[i];
        }
    }
    return NULL;
}

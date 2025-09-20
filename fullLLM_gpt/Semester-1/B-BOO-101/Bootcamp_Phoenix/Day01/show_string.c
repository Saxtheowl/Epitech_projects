#include "phoenix.h"

int show_string(char const *str)
{
    if (!str) {
        return 0;
    }
    for (int i = 0; str[i] != '\0'; ++i) {
        my_putchar(str[i]);
    }
    return 0;
}

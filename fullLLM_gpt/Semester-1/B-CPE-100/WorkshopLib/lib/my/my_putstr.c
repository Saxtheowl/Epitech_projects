#include "my.h"

int my_putstr(char const *str)
{
    int count = 0;

    if (str == 0)
        return 0;
    while (str[count] != '\0') {
        my_putchar(str[count]);
        ++count;
    }
    return count;
}

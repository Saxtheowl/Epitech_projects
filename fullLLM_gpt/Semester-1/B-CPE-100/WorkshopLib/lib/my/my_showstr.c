#include "my.h"

static void put_hex(unsigned char value)
{
    const char *base = "0123456789abcdef";

    my_putchar('\\');
    my_putchar(base[value / 16]);
    my_putchar(base[value % 16]);
}

int my_showstr(char const *str)
{
    if (str == 0)
        return 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        unsigned char c = (unsigned char)str[i];
        if (c >= 32 && c != 127) {
            my_putchar((char)c);
        } else {
            put_hex(c);
        }
    }
    return 0;
}

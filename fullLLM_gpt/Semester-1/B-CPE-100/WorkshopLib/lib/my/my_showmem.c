#include "my.h"

static void put_hex_value(unsigned int value, int digits)
{
    const char *base = "0123456789abcdef";

    for (int i = digits - 1; i >= 0; --i) {
        unsigned int nibble = (value >> (i * 4)) & 0xF;
        my_putchar(base[nibble]);
    }
}

static void put_hex_byte(unsigned char value)
{
    const char *base = "0123456789abcdef";

    my_putchar(base[value >> 4]);
    my_putchar(base[value & 0xF]);
}

int my_showmem(char const *str, int size)
{
    if (str == 0 || size <= 0)
        return 0;

    const unsigned char *bytes = (const unsigned char *)str;

    for (int offset = 0; offset < size; offset += 16) {
        int chunk = size - offset;
        if (chunk > 16)
            chunk = 16;

        put_hex_value((unsigned int)offset, 8);
        my_putchar(':');
        my_putchar(' ');

        for (int i = 0; i < 16; ++i) {
            if (i < chunk) {
                put_hex_byte(bytes[offset + i]);
            } else {
                my_putchar(' ');
                my_putchar(' ');
            }
            if (i % 2 == 1)
                my_putchar(' ');
        }

        for (int i = 0; i < chunk; ++i) {
            unsigned char c = bytes[offset + i];
            if (c < 32 || c == 127)
                my_putchar('.');
            else
                my_putchar((char)c);
        }
        my_putchar('\n');
    }
    return 0;
}

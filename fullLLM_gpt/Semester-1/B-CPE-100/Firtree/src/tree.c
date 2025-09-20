#include <unistd.h>

#include "tree.h"

static void put_char(char c)
{
    (void)!write(1, &c, 1);
}

static void put_nchar(char c, int count)
{
    for (int i = 0; i < count; ++i) {
        put_char(c);
    }
}

static int compute_base_width(int size)
{
    int width = 1;
    int dec = 2;
    int dec_increase = 0;

    for (int block = 1; block <= size; ++block) {
        int lines = block + 3;
        for (int line = 0; line < lines; ++line) {
            if (block != size || line != lines - 1) {
                width += 2;
            }
        }
        if (block != size) {
            width -= 2 * dec;
            if (++dec_increase == 2) {
                ++dec;
                dec_increase = 0;
            }
        }
    }
    return width;
}

void tree(int size)
{
    if (size <= 0) {
        return;
    }

    int width = compute_base_width(size);
    int stars = 1;
    int dec = 2;
    int dec_increase = 0;

    for (int block = 1; block <= size; ++block) {
        int lines = block + 3;
        for (int line = 0; line < lines; ++line) {
            int spaces = (width - stars) / 2;
            put_nchar(' ', spaces);
            put_nchar('*', stars);
            put_char('\n');
            stars += 2;
        }
        if (block != size) {
            stars -= 2 * dec;
            if (++dec_increase == 2) {
                ++dec;
                dec_increase = 0;
            }
        }
    }

    int trunk_width = (size % 2 == 0) ? size + 1 : size;
    int trunk_height = size;
    int trunk_spaces = (width - trunk_width) / 2;

    for (int h = 0; h < trunk_height; ++h) {
        put_nchar(' ', trunk_spaces);
        put_nchar('|', trunk_width);
        put_char('\n');
    }
}

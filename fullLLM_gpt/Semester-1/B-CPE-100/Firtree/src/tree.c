#include <stdio.h>
#include "tree.h"

static void putnchar(char c, int n)
{
    for (int i = 0; i < n; ++i)
        putchar(c);
}

static int last_line_stars(int size)
{
    int stars = 1;
    int dec = 2; // initial decrement after each block
    int dec_increase_counter = 0;
    for (int block = 1; block <= size; ++block) {
        int lines = block + 3;
        for (int l = 0; l < lines; ++l) {
            if (!(block == size && l == lines - 1))
                stars += 2;
        }
        if (block != size) {
            stars -= 2 * dec;
            dec_increase_counter++;
            if (dec_increase_counter == 2) {
                dec++;
                dec_increase_counter = 0;
            }
        }
    }
    return stars;
}

void print_tree(int size)
{
    int stars = 1;
    int dec = 2;
    int dec_inc_cnt = 0;
    int width = last_line_stars(size);
    int trunk_w = (size % 2 == 0) ? size + 1 : size;
    int trunk_h = size;

    for (int block = 1; block <= size; ++block) {
        int lines = block + 3;
        for (int l = 0; l < lines; ++l) {
            int spaces = (width - stars) / 2;
            putnchar(' ', spaces);
            putnchar('*', stars);
            putchar('\n');
            stars += 2;
        }
        if (block != size) {
            stars -= 2 * dec;
            dec_inc_cnt++;
            if (dec_inc_cnt == 2) {
                dec++;
                dec_inc_cnt = 0;
            }
        }
    }

    int spaces = (width - trunk_w) / 2;
    for (int i = 0; i < trunk_h; ++i) {
        putnchar(' ', spaces);
        putnchar('|', trunk_w);
        putchar('\n');
    }
}

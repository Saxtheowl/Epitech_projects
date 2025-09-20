#include <unistd.h>

#include "rush.h"

void my_putchar(char c);

static void print_error(void)
{
    static const char msg[] = "Invalid size\n";

    (void)!write(2, msg, sizeof(msg) - 1);
}

static char tile_for(int x, int y, int width, int height)
{
    int last_col = width - 1;
    int last_row = height - 1;

    if (width == 1 || height == 1)
        return 'B';
    if (y == 0 && (x == 0 || x == last_col))
        return 'A';
    if (y == last_row && (x == 0 || x == last_col))
        return 'C';
    if (y == 0 || y == last_row || x == 0 || x == last_col)
        return 'B';
    return ' ';
}

void rush(int x, int y)
{
    if (x <= 0 || y <= 0) {
        print_error();
        return;
    }
    for (int row = 0; row < y; ++row) {
        for (int col = 0; col < x; ++col)
            my_putchar(tile_for(col, row, x, y));
        my_putchar('\n');
    }
}

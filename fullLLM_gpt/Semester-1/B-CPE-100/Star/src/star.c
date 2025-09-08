#include <stdio.h>
#include "star.h"

static void putnchar(char c, int n)
{
    for (int i = 0; i < n; ++i)
        putchar(c);
}

static void line_one_star(int indent)
{
    putnchar(' ', indent);
    putchar('*');
    putchar('\n');
}

static void line_two_stars(int left_spaces, int inner_spaces)
{
    putnchar(' ', left_spaces);
    putchar('*');
    putnchar(' ', inner_spaces);
    putchar('*');
    putchar('\n');
}

void print_star(int s)
{
    int w = 2 * s + 1;
    int g = (2 * s - 3);
    if (g < 1) g = 1;
    int T = 2 * w + g;

    int apex_indent = w + (g / 2);
    line_one_star(apex_indent);
    for (int i = 1; i <= s - 1; ++i) {
        int left_spaces = apex_indent - i;
        int inner_spaces = 2 * i - 1;
        line_two_stars(left_spaces, inner_spaces);
    }

    putnchar('*', w);
    putnchar(' ', g);
    putnchar('*', w);
    putchar('\n');

    for (int L = 1; L <= s; ++L) {
        int inner = T - 2 * L - 2;
        line_two_stars(L, inner);
    }
    for (int L = s - 1; L >= 1; --L) {
        int inner = T - 2 * L - 2;
        line_two_stars(L, inner);
    }

    putnchar('*', w);
    putnchar(' ', g);
    putnchar('*', w);
    putchar('\n');

    for (int i = s - 1; i >= 1; --i) {
        int left_spaces = apex_indent - i;
        int inner_spaces = 2 * i - 1;
        line_two_stars(left_spaces, inner_spaces);
    }
    line_one_star(apex_indent);
}

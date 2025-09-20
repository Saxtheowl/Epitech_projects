#include <unistd.h>

#include "star.h"

static void put_char(char c)
{
    (void)!write(1, &c, 1);
}

static void put_nchar(char c, unsigned int count)
{
    for (unsigned int i = 0; i < count; ++i) {
        put_char(c);
    }
}

static void line_one_star(unsigned int indent)
{
    put_nchar(' ', indent);
    put_char('*');
    put_char('\n');
}

static void line_two_stars(unsigned int left_spaces, unsigned int inner_spaces)
{
    put_nchar(' ', left_spaces);
    put_char('*');
    put_nchar(' ', inner_spaces);
    put_char('*');
    put_char('\n');
}

void star(unsigned int size)
{
    if (size == 0) {
        return;
    }

    unsigned int w = 2 * size + 1;
    unsigned int g = (size > 1) ? (2 * size - 3) : 1;
    unsigned int span = (2 * w) + g;
    unsigned int apex_indent = w + (g / 2);

    line_one_star(apex_indent);

    for (unsigned int i = 1; i < size; ++i) {
        unsigned int left_spaces = apex_indent - i;
        unsigned int inner_spaces = (2 * i) - 1;
        line_two_stars(left_spaces, inner_spaces);
    }

    put_nchar('*', w);
    put_nchar(' ', g);
    put_nchar('*', w);
    put_char('\n');

    for (unsigned int arm = 1; arm <= size; ++arm) {
        unsigned int inner = span - (2 * arm) - 2;
        line_two_stars(arm, inner);
    }

    for (unsigned int arm = size; arm-- > 1;) {
        unsigned int inner = span - (2 * arm) - 2;
        line_two_stars(arm, inner);
    }

    put_nchar('*', w);
    put_nchar(' ', g);
    put_nchar('*', w);
    put_char('\n');

    for (unsigned int i = size; i-- > 1;) {
        unsigned int left_spaces = apex_indent - i;
        unsigned int inner_spaces = (2 * i) - 1;
        line_two_stars(left_spaces, inner_spaces);
    }

    line_one_star(apex_indent);
}

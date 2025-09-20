#include "phoenix.h"

static void print_combination(char a, char b, char c, int is_last)
{
    my_putchar(a);
    my_putchar(b);
    my_putchar(c);
    if (!is_last) {
        my_putchar(',');
        my_putchar(' ');
    }
}

int show_combinations(void)
{
    for (char a = '0'; a <= '7'; ++a) {
        for (char b = a + 1; b <= '8'; ++b) {
            for (char c = b + 1; c <= '9'; ++c) {
                int is_last = (a == '7' && b == '8' && c == '9');
                print_combination(a, b, c, is_last);
            }
        }
    }
    my_putchar('\n');
    return 0;
}

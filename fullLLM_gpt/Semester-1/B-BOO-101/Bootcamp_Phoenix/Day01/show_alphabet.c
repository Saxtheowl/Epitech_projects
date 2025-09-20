#include "phoenix.h"

int show_alphabet(void)
{
    for (char c = 'a'; c <= 'z'; ++c) {
        my_putchar(c);
    }
    my_putchar('\n');
    return 0;
}

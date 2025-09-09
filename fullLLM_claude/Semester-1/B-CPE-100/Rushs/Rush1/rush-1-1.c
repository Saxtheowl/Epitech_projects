#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

void rush(int x, int y)
{
    int i, j;
    
    if (x <= 0 || y <= 0)
        return;
    
    for (i = 0; i < y; i++) {
        for (j = 0; j < x; j++) {
            if ((i == 0 || i == y - 1) && (j == 0 || j == x - 1)) {
                my_putchar('o');
            } else if (i == 0 || i == y - 1) {
                my_putchar('-');
            } else if (j == 0 || j == x - 1) {
                my_putchar('|');
            } else {
                my_putchar(' ');
            }
        }
        my_putchar('\n');
    }
}
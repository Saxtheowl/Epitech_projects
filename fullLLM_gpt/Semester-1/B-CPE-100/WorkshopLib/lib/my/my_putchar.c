#include <unistd.h>

void my_putchar(char c)
{
    (void)!write(1, &c, 1);
}

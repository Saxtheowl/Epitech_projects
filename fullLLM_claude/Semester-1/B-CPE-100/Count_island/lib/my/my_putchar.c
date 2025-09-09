#include <unistd.h>

int my_putchar(char c)
{
    return write(1, &c, 1);
}
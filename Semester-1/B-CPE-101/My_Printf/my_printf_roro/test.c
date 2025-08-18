#include "my.h"

int main(void)
{
    char str[8];
    my_strcpy(str, "world!");
    my_printf("Hello %s\n", str);
    
    my_printf("Number: %d\n", 42);
    my_printf("Negative: %d\n", -42);
    my_printf("Hex: %x\n", 255);
    my_printf("Hex upper: %X\n", 255);
    my_printf("Octal: %o\n", 64);
    my_printf("Unsigned: %u\n", 4294967295U);
    my_printf("Character: %c\n", 'A');
    my_printf("Percent: %%\n");
    
    return 0;
}
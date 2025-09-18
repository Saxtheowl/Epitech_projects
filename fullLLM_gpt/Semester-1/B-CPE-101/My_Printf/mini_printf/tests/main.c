#include <stdio.h>
#include "mini_printf.h"

int main(void)
{
    mini_printf("Hello %s!\n", "world");
    mini_printf("Char: %c, Num: %d, Lit: %%\n", 'A', 42);
    mini_printf("Neg: %d; Null:%s\n", -123, (char*)0);
    mini_printf("Unknown:%q stays literal\n");
    return 0;
}

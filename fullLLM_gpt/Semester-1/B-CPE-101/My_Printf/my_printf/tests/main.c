#include <stdio.h>
#include "my_printf.h"

int main(void)
{
    my_printf("Hello %s!\n", "world");
    my_printf("Char:%c Num:%d Int:%i Uns:%u Oct:%o Hex:%x HEX:%X Ptr:%p End:%%\n",
              'Z', -42, 1337, 4294967295u, 0777u, 0xdeadbeefu, 0xBEEF, (void*)0x1234);
    my_printf("Null:%s Zero:%u\n", (char*)0, 0u);
    return 0;
}


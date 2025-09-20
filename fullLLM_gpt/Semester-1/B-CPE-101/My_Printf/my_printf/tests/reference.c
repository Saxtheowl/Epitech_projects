#include <stdio.h>
#include <limits.h>

int main(void)
{
    printf("Hello %s!\n", "world");
    printf("Char:%c Num:%d Int:%i Uns:%u Oct:%#o Hex:%#x HEX:%#X Ptr:%p End:%%\n",
           'Z', -42, 1337, 4294967295u, 0777u, 0xdeadbeef, 0xBEEF, (void *)0x1234);
    printf("Null:%s Zero:%u\n", "(null)", 0u);

    printf("Width:%10d Left:%-10d Zero:%010d Prec:%.5d\n", 123, 123, 123, 123);
    printf("Plus:%+d Space:% d Zero:%0d\n", 42, 42, 0);
    printf("Alt hex zero:%#x alt oct zero:%#o\n", 0u, 0u);

    printf("Dyn width:%*d Dyn prec:%.*f Both:%*.*x\n", 8, 321, 3, 3.14159, 12, 4, 0xABCD);
    printf("Float:%f | Prec:%#.0f | Sci:%E | sci-neg:%e\n", 123.456, 3.0, 123.456, -0.00123);
    printf("Pointer null:%p\n", (void *)0);

    printf("Long:%ld LongLong:%lld UnsLong:%llu\n",
           2147483648L, -9223372036854775807LL - 1, 18446744073709551615ULL);

    printf("Mixed:%-#10x %+10d % 10i\n", 0x2a, 42, -42);
    return 0;
}

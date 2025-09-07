void my_putchar(char c);

int my_print_comb(void)
{
    int a = 0;
    int b;
    int c;
    int first = 1;

    while (a <= 7) {
        b = a + 1;
        while (b <= 8) {
            c = b + 1;
            while (c <= 9) {
                if (!first) {
                    my_putchar(',');
                    my_putchar(' ');
                }
                my_putchar('0' + a);
                my_putchar('0' + b);
                my_putchar('0' + c);
                first = 0;
                c++;
            }
            b++;
        }
        a++;
    }
    return 0;
}
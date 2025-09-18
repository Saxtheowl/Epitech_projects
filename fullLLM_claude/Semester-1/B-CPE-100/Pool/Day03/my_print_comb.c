int my_print_comb(void)
{
    int i = 0;
    int j = 1;
    int k = 2;
    int first = 1;
    
    while (i <= 7) {
        j = i + 1;
        while (j <= 8) {
            k = j + 1;
            while (k <= 9) {
                if (!first) {
                    my_putchar(',');
                    my_putchar(' ');
                }
                first = 0;
                my_putchar('0' + i);
                my_putchar('0' + j);
                my_putchar('0' + k);
                k++;
            }
            j++;
        }
        i++;
    }
    return (0);
}
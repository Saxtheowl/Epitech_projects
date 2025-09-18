int my_print_comb2(void)
{
    int first_num = 0;
    int second_num = 1;
    int first = 1;
    
    while (first_num <= 98) {
        second_num = first_num + 1;
        while (second_num <= 99) {
            if (!first) {
                my_putchar(',');
                my_putchar(' ');
            }
            first = 0;
            my_putchar('0' + first_num / 10);
            my_putchar('0' + first_num % 10);
            my_putchar(' ');
            my_putchar('0' + second_num / 10);
            my_putchar('0' + second_num % 10);
            second_num++;
        }
        first_num++;
    }
    return (0);
}
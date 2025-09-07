void my_putchar(char c);

int my_print_comb2(void)
{
    int first_nb = 0;
    int second_nb;
    int first = 1;

    while (first_nb <= 98) {
        second_nb = first_nb + 1;
        while (second_nb <= 99) {
            if (!first) {
                my_putchar(',');
                my_putchar(' ');
            }
            my_putchar('0' + (first_nb / 10));
            my_putchar('0' + (first_nb % 10));
            my_putchar(' ');
            my_putchar('0' + (second_nb / 10));
            my_putchar('0' + (second_nb % 10));
            first = 0;
            second_nb++;
        }
        first_nb++;
    }
    return 0;
}
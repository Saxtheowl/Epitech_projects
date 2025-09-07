void my_putchar(char c);

int my_print_alpha(void)
{
    char c = 'a';

    while (c <= 'z') {
        my_putchar(c);
        c++;
    }
    return 0;
}
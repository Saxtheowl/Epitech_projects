int my_print_digits(void)
{
    char c = '0';
    
    while (c <= '9') {
        my_putchar(c);
        c++;
    }
    return (0);
}
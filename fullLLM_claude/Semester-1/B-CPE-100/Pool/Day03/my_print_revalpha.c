int my_print_revalpha(void)
{
    char c = 'z';
    
    while (c >= 'a') {
        my_putchar(c);
        c--;
    }
    return (0);
}
void my_putchar(char c);

void my_putstr(char const *str)
{
    int i = 0;
    
    if (str == 0)
        return;
    
    while (str[i]) {
        my_putchar(str[i]);
        i++;
    }
}
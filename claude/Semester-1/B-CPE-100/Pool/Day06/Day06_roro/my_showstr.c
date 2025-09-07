void my_putchar(char c);

static void print_hex(unsigned char c)
{
    char hex[] = "0123456789abcdef";
    
    my_putchar(hex[c / 16]);
    my_putchar(hex[c % 16]);
}

int my_showstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= 32 && str[i] <= 126) {
            my_putchar(str[i]);
        } else {
            my_putchar('\\');
            if ((unsigned char)str[i] < 16)
                my_putchar('0');
            print_hex((unsigned char)str[i]);
        }
        i++;
    }
    return 0;
}
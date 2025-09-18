/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** my_showstr.c
*/

void my_putchar(char c);

static int is_printable(char c)
{
    return (c >= 32 && c <= 126);
}

static void print_hex(unsigned char c)
{
    char hex[] = "0123456789abcdef";
    
    my_putchar('\\');
    if (c < 16)
        my_putchar('0');
    if (c >= 16)
        my_putchar(hex[c / 16]);
    my_putchar(hex[c % 16]);
}

int my_showstr(char const *str)
{
    int i = 0;
    
    while (str[i] != '\0') {
        if (is_printable(str[i])) {
            my_putchar(str[i]);
        } else {
            print_hex((unsigned char)str[i]);
        }
        i++;
    }
    
    return 0;
}
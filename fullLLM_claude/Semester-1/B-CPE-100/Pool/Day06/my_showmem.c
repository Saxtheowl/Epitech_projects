/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** my_showmem.c
*/

void my_putchar(char c);

static void print_hex_addr(int addr)
{
    char hex[] = "0123456789abcdef";
    int i;
    
    for (i = 7; i >= 0; i--) {
        my_putchar(hex[(addr >> (i * 4)) & 0xf]);
    }
    my_putchar(':');
    my_putchar(' ');
}

static void print_hex_byte(unsigned char byte)
{
    char hex[] = "0123456789abcdef";
    
    my_putchar(hex[byte >> 4]);
    my_putchar(hex[byte & 0xf]);
}

static void print_hex_content(char const *str, int size, int line_start)
{
    int i;
    
    for (i = 0; i < 16; i++) {
        if (line_start + i < size) {
            print_hex_byte((unsigned char)str[line_start + i]);
        } else {
            my_putchar(' ');
            my_putchar(' ');
        }
        
        if (i % 2 == 1)
            my_putchar(' ');
    }
}

static void print_printable_content(char const *str, int size, int line_start)
{
    int i;
    
    for (i = 0; i < 16 && line_start + i < size; i++) {
        char c = str[line_start + i];
        if (c >= 32 && c <= 126) {
            my_putchar(c);
        } else {
            my_putchar('.');
        }
    }
}

int my_showmem(char const *str, int size)
{
    int i = 0;
    
    while (i < size) {
        print_hex_addr(i);
        print_hex_content(str, size, i);
        print_printable_content(str, size, i);
        my_putchar('\n');
        i += 16;
    }
    
    return 0;
}
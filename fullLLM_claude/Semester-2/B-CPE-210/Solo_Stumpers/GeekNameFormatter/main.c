/*
** EPITECH PROJECT, 2024
** Geek Name Formatter
** File description:
** Format names according to geek/leet speak conventions
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char *str)
{
    int i = 0;
    
    while (str[i]) {
        my_putchar(str[i]);
        i++;
    }
}

void my_puterr(char *str)
{
    int len = 0;
    
    while (str[len])
        len++;
    write(2, str, len);
}

char to_uppercase(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - ('a' - 'A');
    return c;
}

char to_lowercase(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}

int is_letter(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int is_whitespace(char c)
{
    return (c == ' ' || c == '\t');
}

char replace_leet_char(char c)
{
    char lower = to_lowercase(c);
    
    switch (lower) {
        case 'o': return '0';
        case 'i': return '1';
        case 'u': return '2';
        case 'e': return '3';
        case 'a': return '4';
        case 'y': return '5';
        default: return c;
    }
}

void format_geek_name(char *str)
{
    int i = 0;
    int uppercase = 1; // Start with uppercase
    
    while (str[i]) {
        char c = str[i];
        
        if (is_whitespace(c)) {
            my_putchar(c);
            uppercase = 1; // Reset to uppercase for next word
        } else {
            // Apply leet replacements
            c = replace_leet_char(c);
            
            // Apply alternating case only to letters
            if (is_letter(c)) {
                if (uppercase) {
                    c = to_uppercase(c);
                } else {
                    c = to_lowercase(c);
                }
                uppercase = !uppercase; // Toggle for next letter
            }
            
            my_putchar(c);
        }
        
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        my_puterr("Usage: geekNameFormatter string\n");
        return 84;
    }
    
    format_geek_name(argv[1]);
    my_putchar('\n');
    
    return 0;
}
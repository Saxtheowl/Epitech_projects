/*
** EPITECH PROJECT, 2024
** US Name Formatter
** File description:
** Format names according to US conventions
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

int my_strlen(char *str)
{
    int len = 0;
    
    while (str[len])
        len++;
    return len;
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

int is_whitespace(char c)
{
    return (c == ' ' || c == '\t');
}

void skip_whitespace(char *str, int *i)
{
    while (str[*i] && is_whitespace(str[*i]))
        (*i)++;
}

int get_word_length(char *str, int start)
{
    int len = 0;
    
    while (str[start + len] && !is_whitespace(str[start + len]))
        len++;
    return len;
}

void format_first_name(char *str, int start, int len)
{
    int i;
    
    if (len == 2) {
        // 2-letter first name: print in upper case
        for (i = 0; i < len; i++) {
            my_putchar(to_uppercase(str[start + i]));
        }
    } else if (len == 1) {
        // Single letter: print in upper case followed by dot
        my_putchar(to_uppercase(str[start]));
        my_putchar('.');
    } else {
        // More than 2 letters: only first letter uppercase
        my_putchar(to_uppercase(str[start]));
        for (i = 1; i < len; i++) {
            my_putchar(to_lowercase(str[start + i]));
        }
    }
}

void format_last_name_word(char *str, int start, int len)
{
    int i;
    
    // First letter uppercase, others lowercase
    my_putchar(to_uppercase(str[start]));
    for (i = 1; i < len; i++) {
        my_putchar(to_lowercase(str[start + i]));
    }
}

void format_name(char *str)
{
    int i = 0;
    int word_start, word_len;
    int first_name_done = 0;
    int first_word = 1;
    
    while (str[i]) {
        skip_whitespace(str, &i);
        if (!str[i])
            break;
            
        word_start = i;
        word_len = get_word_length(str, i);
        i += word_len;
        
        if (!first_name_done) {
            // Check if this is a single letter followed by more words (middle initial)
            int temp_i = i;
            skip_whitespace(str, &temp_i);
            if (word_len == 1 && str[temp_i]) {
                // Single letter, format as initial with dot
                if (!first_word)
                    my_putchar(' ');
                format_first_name(str, word_start, word_len);
                first_word = 0;
                continue;
            } else {
                // This is the main first name
                if (!first_word)
                    my_putchar(' ');
                format_first_name(str, word_start, word_len);
                first_name_done = 1;
                first_word = 0;
            }
        } else {
            // Last name words
            if (!first_word)
                my_putchar(' ');
            format_last_name_word(str, word_start, word_len);
            first_word = 0;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        my_puterr("Usage: USNameFormatter string\n");
        return 84;
    }
    
    format_name(argv[1]);
    my_putchar('\n');
    
    return 0;
}
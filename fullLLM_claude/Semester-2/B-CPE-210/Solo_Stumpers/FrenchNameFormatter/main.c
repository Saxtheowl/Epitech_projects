/*
** EPITECH PROJECT, 2024
** French Name Formatter
** File description:
** Format names according to French conventions
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

void format_first_name_word(char *str, int start, int len)
{
    int i;
    int first_of_subword = 1;
    
    for (i = 0; i < len; i++) {
        if (str[start + i] == '-') {
            my_putchar('-');
            first_of_subword = 1;
        } else if (first_of_subword) {
            my_putchar(to_uppercase(str[start + i]));
            first_of_subword = 0;
        } else {
            my_putchar(to_lowercase(str[start + i]));
        }
    }
}

void format_last_name_word(char *str, int start, int len)
{
    int i;
    
    // All letters uppercase
    for (i = 0; i < len; i++) {
        my_putchar(to_uppercase(str[start + i]));
    }
}

int find_last_name_start(char *str)
{
    int i = 0;
    int word_count = 0;
    int last_word_start = 0;
    
    while (str[i]) {
        skip_whitespace(str, &i);
        if (!str[i])
            break;
            
        if (word_count == 0) {
            // First word - check if it contains hyphen
            int word_len = get_word_length(str, i);
            int j;
            int has_hyphen = 0;
            
            for (j = 0; j < word_len; j++) {
                if (str[i + j] == '-') {
                    has_hyphen = 1;
                    break;
                }
            }
            
            if (has_hyphen) {
                // First name is compound, skip this entire word
                i += word_len;
                word_count++;
                continue;
            }
        }
        
        if (word_count >= 1) {
            // This is part of last name
            last_word_start = i;
            break;
        }
        
        i += get_word_length(str, i);
        word_count++;
    }
    
    return last_word_start;
}

void format_name(char *str)
{
    int i = 0;
    int last_name_start = find_last_name_start(str);
    int first_word = 1;
    
    // Format first name part
    while (str[i] && i < last_name_start) {
        skip_whitespace(str, &i);
        if (!str[i] || i >= last_name_start)
            break;
            
        int word_start = i;
        int word_len = get_word_length(str, i);
        
        if (!first_word)
            my_putchar(' ');
            
        format_first_name_word(str, word_start, word_len);
        i += word_len;
        first_word = 0;
    }
    
    // Format last name part
    if (str[last_name_start]) {
        my_putchar(' '); // Space between first and last name
        first_word = 1;
        i = last_name_start;
        
        while (str[i]) {
            skip_whitespace(str, &i);
            if (!str[i])
                break;
                
            int word_start = i;
            int word_len = get_word_length(str, i);
            
            if (!first_word)
                my_putchar(' ');
                
            format_last_name_word(str, word_start, word_len);
            i += word_len;
            first_word = 0;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        my_puterr("Usage: frenchNameFormatter string\n");
        return 84;
    }
    
    format_name(argv[1]);
    my_putchar('\n');
    
    return 0;
}
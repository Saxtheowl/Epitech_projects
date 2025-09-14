/*
** EPITECH PROJECT, 2024
** Clean String
** File description:
** Clean string by removing extra spaces and tabs
*/

#include <unistd.h>

int is_whitespace(char c)
{
    return (c == ' ' || c == '\t');
}

void my_putchar(char c)
{
    write(1, &c, 1);
}

void clean_string(char *str)
{
    int i = 0;
    int in_word = 0;
    int first_word = 1;
    
    while (str[i]) {
        if (!is_whitespace(str[i])) {
            if (!in_word) {
                if (!first_word) {
                    my_putchar(' ');
                }
                first_word = 0;
                in_word = 1;
            }
            my_putchar(str[i]);
        } else {
            in_word = 0;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        my_putchar('\n');
        return 0;
    }
    
    if (argc == 2) {
        clean_string(argv[1]);
        my_putchar('\n');
    }
    
    return 0;
}
/*
** EPITECH PROJECT, 2024
** Anagram
** File description:
** Check if two strings are anagrams
*/

#include <unistd.h>

int my_strlen(char *str)
{
    int len = 0;
    
    while (str[len])
        len++;
    return len;
}

void my_putstr(char *str)
{
    write(1, str, my_strlen(str));
}

void my_puterr(char *str)
{
    write(2, str, my_strlen(str));
}

char to_lowercase(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}

int is_alphabetic(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int count_char(char *str, char c)
{
    int count = 0;
    int i = 0;
    
    while (str[i]) {
        if (is_alphabetic(str[i]) && to_lowercase(str[i]) == to_lowercase(c))
            count++;
        i++;
    }
    return count;
}

int check_anagram(char *str1, char *str2)
{
    int i = 0;
    int j;
    char processed[256] = {0};
    int processed_count = 0;
    
    while (str1[i]) {
        if (is_alphabetic(str1[i])) {
            char current = to_lowercase(str1[i]);
            int already_processed = 0;
            
            for (j = 0; j < processed_count; j++) {
                if (processed[j] == current) {
                    already_processed = 1;
                    break;
                }
            }
            
            if (!already_processed) {
                if (count_char(str1, current) != count_char(str2, current))
                    return 0;
                processed[processed_count++] = current;
            }
        }
        i++;
    }
    
    i = 0;
    while (str2[i]) {
        if (is_alphabetic(str2[i])) {
            char current = to_lowercase(str2[i]);
            int already_processed = 0;
            
            for (j = 0; j < processed_count; j++) {
                if (processed[j] == current) {
                    already_processed = 1;
                    break;
                }
            }
            
            if (!already_processed) {
                if (count_char(str1, current) != count_char(str2, current))
                    return 0;
                processed[processed_count++] = current;
            }
        }
        i++;
    }
    
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        my_puterr("Error: not enough arguments.\n");
        return 84;
    }
    
    if (check_anagram(argv[1], argv[2]))
        my_putstr("anagram!\n");
    else
        my_putstr("no anagrams.\n");
    
    return 0;
}
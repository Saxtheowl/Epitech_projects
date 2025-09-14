/*
** EPITECH PROJECT, 2024
** Sort Words
** File description:
** Sort words in alphabetical order maintaining original order for duplicates
*/

#include <unistd.h>
#include <stdlib.h>

int my_strlen(char *str)
{
    int len = 0;
    
    while (str[len])
        len++;
    return len;
}

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

int is_whitespace(char c)
{
    return (c == ' ' || c == '\t');
}

char to_lowercase(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}

int my_strcasecmp(char *s1, char *s2)
{
    int i = 0;
    
    while (s1[i] && s2[i]) {
        char c1 = to_lowercase(s1[i]);
        char c2 = to_lowercase(s2[i]);
        
        if (c1 < c2)
            return -1;
        if (c1 > c2)
            return 1;
        i++;
    }
    
    if (s1[i] && !s2[i])
        return 1;
    if (!s1[i] && s2[i])
        return -1;
    
    return 0;
}

char **extract_words(char *str, int *word_count)
{
    char **words;
    int i = 0, j, k;
    int count = 0;
    int word_start;
    
    // Count words
    while (str[i]) {
        if (!is_whitespace(str[i])) {
            count++;
            while (str[i] && !is_whitespace(str[i]))
                i++;
        } else {
            i++;
        }
    }
    
    if (count == 0) {
        *word_count = 0;
        return NULL;
    }
    
    words = malloc(sizeof(char*) * count);
    if (!words)
        return NULL;
    
    i = 0;
    j = 0;
    while (str[i] && j < count) {
        if (!is_whitespace(str[i])) {
            word_start = i;
            while (str[i] && !is_whitespace(str[i]))
                i++;
            
            words[j] = malloc(sizeof(char) * (i - word_start + 1));
            if (!words[j]) {
                for (k = 0; k < j; k++)
                    free(words[k]);
                free(words);
                return NULL;
            }
            
            for (k = 0; k < i - word_start; k++)
                words[j][k] = str[word_start + k];
            words[j][k] = '\0';
            j++;
        } else {
            i++;
        }
    }
    
    *word_count = count;
    return words;
}

void sort_words(char **words, int count)
{
    int i, j;
    char *temp;
    
    // Stable insertion sort
    for (i = 1; i < count; i++) {
        temp = words[i];
        j = i - 1;
        
        while (j >= 0 && my_strcasecmp(words[j], temp) > 0) {
            words[j + 1] = words[j];
            j--;
        }
        words[j + 1] = temp;
    }
}

int main(int argc, char **argv)
{
    char **words;
    int word_count;
    int i;
    
    if (argc == 1) {
        my_putchar('\n');
        return 0;
    }
    
    if (argc != 2) {
        return 0;
    }
    
    words = extract_words(argv[1], &word_count);
    if (!words || word_count == 0) {
        my_putchar('\n');
        return 0;
    }
    
    sort_words(words, word_count);
    
    for (i = 0; i < word_count; i++) {
        if (i > 0)
            my_putchar(' ');
        my_putstr(words[i]);
    }
    my_putchar('\n');
    
    for (i = 0; i < word_count; i++)
        free(words[i]);
    free(words);
    
    return 0;
}
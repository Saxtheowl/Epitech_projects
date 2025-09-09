#include "organized.h"

static int count_words(char const *str, char sep)
{
    int count = 0;
    int in_word = 0;
    int i = 0;
    
    while (str[i]) {
        if (str[i] != sep && str[i] != ' ' && str[i] != '\t') {
            if (!in_word) {
                count++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
        i++;
    }
    
    return count;
}

static char *extract_word(char const *str, int start, int end)
{
    int len = end - start;
    char *word = malloc(len + 1);
    int i;
    
    if (!word)
        return 0;
    
    for (i = 0; i < len; i++) {
        word[i] = str[start + i];
    }
    word[i] = '\0';
    
    return word;
}

char **split_string(char const *str, char sep)
{
    int word_count = count_words(str, sep);
    char **result = malloc((word_count + 1) * sizeof(char *));
    int i = 0, word_idx = 0;
    int word_start = -1;
    
    if (!result || !str)
        return 0;
    
    while (str[i]) {
        if (str[i] != sep && str[i] != ' ' && str[i] != '\t') {
            if (word_start == -1)
                word_start = i;
        } else {
            if (word_start != -1) {
                result[word_idx] = extract_word(str, word_start, i);
                word_idx++;
                word_start = -1;
            }
        }
        i++;
    }
    
    if (word_start != -1) {
        result[word_idx] = extract_word(str, word_start, i);
        word_idx++;
    }
    
    result[word_idx] = 0;
    return result;
}

void free_string_array(char **array)
{
    int i;
    
    if (!array)
        return;
    
    for (i = 0; array[i]; i++) {
        free(array[i]);
    }
    free(array);
}

int count_args(char **args)
{
    int count = 0;
    
    if (!args)
        return 0;
    
    while (args[count])
        count++;
    
    return count;
}
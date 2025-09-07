#include <stdlib.h>

int my_strlen(char const *str);

static int is_alphanum(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'));
}

static int count_words(char const *str)
{
    int count = 0;
    int i = 0;
    int in_word = 0;

    while (str[i] != '\0') {
        if (is_alphanum(str[i])) {
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

static char *my_strndup(char const *str, int n)
{
    char *result = malloc(n + 1);
    int i = 0;

    if (result == NULL)
        return NULL;

    while (i < n && str[i] != '\0') {
        result[i] = str[i];
        i++;
    }
    result[i] = '\0';
    return result;
}

char **my_str_to_word_array(char const *str)
{
    char **array;
    int words = count_words(str);
    int i = 0, j = 0, start = 0;
    int in_word = 0;

    if (str == NULL)
        return NULL;

    array = malloc(sizeof(char *) * (words + 1));
    if (array == NULL)
        return NULL;

    while (str[i] != '\0') {
        if (is_alphanum(str[i])) {
            if (!in_word) {
                start = i;
                in_word = 1;
            }
        } else {
            if (in_word) {
                array[j] = my_strndup(&str[start], i - start);
                j++;
                in_word = 0;
            }
        }
        i++;
    }
    
    if (in_word) {
        array[j] = my_strndup(&str[start], i - start);
        j++;
    }

    array[j] = NULL;
    return array;
}
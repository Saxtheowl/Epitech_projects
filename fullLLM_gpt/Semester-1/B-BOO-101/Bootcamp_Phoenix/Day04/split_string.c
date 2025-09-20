#include <stdlib.h>
#include "phoenix.h"

static int is_lower(char c)
{
    return c >= 'a' && c <= 'z';
}

static int is_upper(char c)
{
    return c >= 'A' && c <= 'Z';
}

static int is_digit_char(char c)
{
    return c >= '0' && c <= '9';
}

static int is_alphanumeric(char c)
{
    return is_lower(c) || is_upper(c) || is_digit_char(c);
}

static int count_words(char const *str)
{
    int count = 0;
    int in_word = 0;

    if (!str) {
        return 0;
    }
    for (int i = 0; str[i] != '\0'; ++i) {
        if (is_alphanumeric(str[i])) {
            if (!in_word) {
                ++count;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
    }
    return count;
}

static char *duplicate_slice(char const *start, int length)
{
    char *slice = malloc((length + 1) * sizeof(char));

    if (!slice) {
        return NULL;
    }
    for (int i = 0; i < length; ++i) {
        slice[i] = start[i];
    }
    slice[length] = '\0';
    return slice;
}

static void free_array(char **array, int words)
{
    if (!array) {
        return;
    }
    for (int i = 0; i < words; ++i) {
        free(array[i]);
    }
    free(array);
}

char **split_string(char const *str)
{
    int word_count = count_words(str);
    char **array = malloc((word_count + 1) * sizeof(char *));
    int index = 0;
    int i = 0;

    if (!array) {
        return NULL;
    }
    while (str && str[i] != '\0') {
        if (is_alphanumeric(str[i])) {
            int length = 0;

            while (str[i + length] != '\0' && is_alphanumeric(str[i + length])) {
                ++length;
            }
            array[index] = duplicate_slice(&str[i], length);
            if (!array[index]) {
                free_array(array, index);
                return NULL;
            }
            ++index;
            i += length;
        } else {
            ++i;
        }
    }
    array[index] = NULL;
    return array;
}

#include <stdlib.h>

struct info_param
{
    int length;
    char *str;
    char *copy;
    char **word_array;
};

int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
char **my_str_to_word_array(char const *str);

static char *my_strdup(char const *str)
{
    int len = my_strlen(str);
    char *copy = malloc(len + 1);
    int i = 0;
    
    if (copy == NULL)
        return NULL;
    
    while (str[i] != '\0') {
        copy[i] = str[i];
        i++;
    }
    copy[i] = '\0';
    return copy;
}

struct info_param *my_params_to_array(int ac, char **av)
{
    struct info_param *array;
    int i = 0;

    array = malloc(sizeof(struct info_param) * (ac + 1));
    if (array == NULL)
        return NULL;

    while (i < ac) {
        array[i].length = my_strlen(av[i]);
        array[i].str = av[i];
        array[i].copy = my_strdup(av[i]);
        array[i].word_array = my_str_to_word_array(av[i]);
        i++;
    }

    array[i].length = 0;
    array[i].str = 0;
    array[i].copy = 0;
    array[i].word_array = 0;

    return array;
}
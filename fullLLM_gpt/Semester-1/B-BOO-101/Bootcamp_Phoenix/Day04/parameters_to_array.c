#include <stdlib.h>
#include "phoenix.h"

static int string_length(char const *str)
{
    int length = 0;

    if (!str) {
        return 0;
    }
    while (str[length] != '\0') {
        ++length;
    }
    return length;
}

static void free_params(struct info_param *params, int count)
{
    if (!params) {
        return;
    }
    for (int i = 0; i < count; ++i) {
        free(params[i].copy);
        if (params[i].word_array) {
            for (int j = 0; params[i].word_array[j] != NULL; ++j) {
                free(params[i].word_array[j]);
            }
            free(params[i].word_array);
        }
    }
    free(params);
}

struct info_param *parameters_to_array(int ac, char **av)
{
    struct info_param *params = NULL;

    if (ac < 0 || !av) {
        return NULL;
    }
    params = malloc(sizeof(struct info_param) * (ac + 1));
    if (!params) {
        return NULL;
    }
    for (int i = 0; i < ac; ++i) {
        params[i].length = string_length(av[i]);
        params[i].str = av[i];
        params[i].copy = av[i] ? duplicate_string(av[i]) : NULL;
        params[i].word_array = split_string(av[i]);
        if (av[i] && (!params[i].copy || !params[i].word_array)) {
            free_params(params, i + 1);
            return NULL;
        }
    }
    params[ac].length = 0;
    params[ac].str = NULL;
    params[ac].copy = NULL;
    params[ac].word_array = NULL;
    return params;
}

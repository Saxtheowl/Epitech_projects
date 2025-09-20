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

char *concat_parameters(int ac, char **av)
{
    int total_length = 0;
    int position = 0;
    char *result = NULL;

    if (ac <= 0 || !av) {
        return NULL;
    }
    for (int i = 0; i < ac; ++i) {
        total_length += string_length(av[i]);
        if (i + 1 < ac) {
            total_length += 1;
        }
    }
    result = malloc((total_length + 1) * sizeof(char));
    if (!result) {
        return NULL;
    }
    for (int i = 0; i < ac; ++i) {
        char const *current = av[i];
        int idx = 0;

        while (current && current[idx] != '\0') {
            result[position++] = current[idx++];
        }
        if (i + 1 < ac) {
            result[position++] = '\n';
        }
    }
    result[position] = '\0';
    return result;
}

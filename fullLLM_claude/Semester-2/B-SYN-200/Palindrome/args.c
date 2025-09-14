#include "palindrome.h"

int is_valid_number(char *str)
{
    int i;
    
    if (!str || *str == '\0')
        return 0;
    
    for (i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int parse_args(int argc, char **argv, config_t *config)
{
    int i;
    
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            if (!is_valid_number(argv[i + 1]) || config->mode_n == 0)
                return -1;
            config->n = atoi(argv[i + 1]);
            config->mode_n = 1;
            i++;
        } else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            if (!is_valid_number(argv[i + 1]) || config->mode_n == 1)
                return -1;
            config->p = atoi(argv[i + 1]);
            config->mode_n = 0;
            i++;
        } else if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
            if (!is_valid_number(argv[i + 1]))
                return -1;
            config->base = atoi(argv[i + 1]);
            if (config->base <= 1 || config->base > 10)
                return -1;
            i++;
        } else if (strcmp(argv[i], "-imin") == 0 && i + 1 < argc) {
            if (!is_valid_number(argv[i + 1]))
                return -1;
            config->imin = atoi(argv[i + 1]);
            i++;
        } else if (strcmp(argv[i], "-imax") == 0 && i + 1 < argc) {
            if (!is_valid_number(argv[i + 1]))
                return -1;
            config->imax = atoi(argv[i + 1]);
            i++;
        } else {
            return -1;
        }
    }
    
    if (config->imin > config->imax)
        return -1;
    
    return 0;
}
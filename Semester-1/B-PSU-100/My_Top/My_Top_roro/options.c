#include "my_top.h"

options_t *parse_options(int ac, char **av)
{
    options_t *opts;
    int i;
    
    opts = malloc(sizeof(options_t));
    if (!opts)
        return NULL;
    
    opts->username = NULL;
    opts->delay = 3.0;
    opts->frames = -1;
    opts->current_frame = 0;
    
    for (i = 1; i < ac; i++) {
        if (my_strcmp(av[i], "-U") == 0) {
            if (i + 1 >= ac) {
                free_options(opts);
                return NULL;
            }
            opts->username = my_strdup(av[i + 1]);
            i++;
        } else if (my_strcmp(av[i], "-d") == 0) {
            if (i + 1 >= ac) {
                free_options(opts);
                return NULL;
            }
            opts->delay = my_atof(av[i + 1]);
            if (opts->delay <= 0.0)
                opts->delay = 3.0;
            i++;
        } else if (my_strcmp(av[i], "-n") == 0) {
            if (i + 1 >= ac) {
                free_options(opts);
                return NULL;
            }
            opts->frames = my_atoi(av[i + 1]);
            if (opts->frames <= 0)
                opts->frames = -1;
            i++;
        } else if (my_strcmp(av[i], "-h") == 0) {
            free_options(opts);
            return NULL;
        }
    }
    
    return opts;
}

void free_options(options_t *opts)
{
    if (!opts)
        return;
    
    if (opts->username)
        free(opts->username);
    free(opts);
}
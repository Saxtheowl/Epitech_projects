#include "my_ls.h"

static int is_option(char *arg)
{
    return (arg && arg[0] == '-' && arg[1]);
}

static int parse_option_string(char *opt_str, options_t *opts)
{
    int i = 1;
    
    while (opt_str[i]) {
        switch (opt_str[i]) {
            case 'l':
                opts->flags |= OPT_LONG;
                break;
            case 'a':
                opts->flags |= OPT_ALL;
                break;
            case 'R':
                opts->flags |= OPT_RECUR;
                break;
            case 'd':
                opts->flags |= OPT_DIR;
                break;
            case 'r':
                opts->flags |= OPT_REV;
                break;
            case 't':
                opts->flags |= OPT_TIME;
                break;
            default:
                my_putstr("my_ls: invalid option -- '");
                my_putchar(opt_str[i]);
                my_putstr("'\n");
                return -1;
        }
        i++;
    }
    return 0;
}

options_t *parse_options(int ac, char **av)
{
    options_t *opts;
    int i = 1;
    int file_count = 0;
    
    opts = malloc(sizeof(options_t));
    if (!opts)
        return NULL;
    opts->flags = 0;
    opts->files = NULL;
    opts->file_count = 0;
    
    while (i < ac && is_option(av[i])) {
        if (parse_option_string(av[i], opts) == -1) {
            free(opts);
            return NULL;
        }
        i++;
    }
    
    while (i < ac) {
        file_count++;
        i++;
    }
    
    if (file_count > 0) {
        opts->files = malloc(sizeof(char*) * file_count);
        if (!opts->files) {
            free(opts);
            return NULL;
        }
        i = 1;
        while (i < ac && is_option(av[i]))
            i++;
        file_count = 0;
        while (i < ac) {
            opts->files[file_count] = my_strdup(av[i]);
            if (!opts->files[file_count]) {
                free_options(opts);
                return NULL;
            }
            file_count++;
            i++;
        }
    }
    opts->file_count = file_count;
    return opts;
}

void free_options(options_t *opts)
{
    int i;
    
    if (!opts)
        return;
    if (opts->files) {
        for (i = 0; i < opts->file_count; i++) {
            if (opts->files[i])
                free(opts->files[i]);
        }
        free(opts->files);
    }
    free(opts);
}
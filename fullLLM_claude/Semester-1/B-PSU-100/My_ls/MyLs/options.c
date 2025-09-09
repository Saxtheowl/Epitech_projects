#include "my_ls.h"

static void init_options(options_t *options)
{
    options->all = 0;
    options->long_format = 0;
    options->recursive = 0;
    options->directory = 0;
    options->reverse = 0;
    options->sort_time = 0;
}

static void parse_option_string(char const *str, options_t *options)
{
    int i = 1;
    
    while (str[i]) {
        switch (str[i]) {
            case 'a':
                options->all = 1;
                break;
            case 'l':
                options->long_format = 1;
                break;
            case 'R':
                options->recursive = 1;
                break;
            case 'd':
                options->directory = 1;
                break;
            case 'r':
                options->reverse = 1;
                break;
            case 't':
                options->sort_time = 1;
                break;
        }
        i++;
    }
}

options_t parse_options(int argc, char **argv, char ***files, int *file_count)
{
    options_t options;
    int i;
    char **file_list;
    int files_found = 0;
    
    init_options(&options);
    
    file_list = malloc(argc * sizeof(char *));
    if (!file_list) {
        *files = 0;
        *file_count = 0;
        return options;
    }
    
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] != '\0') {
            parse_option_string(argv[i], &options);
        } else {
            file_list[files_found] = my_strdup(argv[i]);
            files_found++;
        }
    }
    
    if (files_found == 0) {
        file_list[0] = my_strdup(".");
        files_found = 1;
    }
    
    *files = file_list;
    *file_count = files_found;
    
    return options;
}
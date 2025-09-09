#include "my_ls.h"

static void free_file_list(char **files, int count)
{
    int i;
    
    if (!files)
        return;
    
    for (i = 0; i < count; i++) {
        if (files[i])
            free(files[i]);
    }
    free(files);
}

int main(int argc, char **argv)
{
    options_t options;
    char **files;
    int file_count;
    int i;
    int ret = 0;
    
    options = parse_options(argc, argv, &files, &file_count);
    
    if (!files) {
        write(2, "Error\n", 6);
        return 84;
    }
    
    for (i = 0; i < file_count; i++) {
        if (file_count > 1 && !options.directory) {
            my_putstr(files[i]);
            my_putstr(":\n");
        }
        
        if (list_file(files[i], options) != 0)
            ret = 84;
        
        if (i < file_count - 1)
            my_putchar('\n');
    }
    
    free_file_list(files, file_count);
    return ret;
}
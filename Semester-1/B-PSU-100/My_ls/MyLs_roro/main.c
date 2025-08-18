#include "my_ls.h"

int main(int ac, char **av)
{
    options_t *opts;
    int i;
    int ret = 0;

    opts = parse_options(ac, av);
    if (!opts)
        return 84;

    if (opts->file_count == 0) {
        ret = list_directory(".", opts);
    } else {
        for (i = 0; i < opts->file_count; i++) {
            struct stat st;
            
            if (lstat(opts->files[i], &st) == -1) {
                my_putstr("my_ls: cannot access '");
                my_putstr(opts->files[i]);
                my_putstr("': No such file or directory\n");
                ret = 84;
                continue;
            }
            
            if (opts->file_count > 1 && i > 0)
                my_putchar('\n');
                
            if (opts->file_count > 1) {
                my_putstr(opts->files[i]);
                my_putstr(":\n");
            }
            
            if (S_ISDIR(st.st_mode) && !(opts->flags & OPT_DIR)) {
                if (list_directory(opts->files[i], opts) != 0)
                    ret = 84;
            } else {
                if (list_file(opts->files[i], opts) != 0)
                    ret = 84;
            }
        }
    }

    free_options(opts);
    return ret;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/my_ls.h"

static void usage(const char *prog)
{
    fprintf(stderr, "Usage: %s [-alRt] [file ...]\n", prog);
}

int run_ls(int argc, char **argv)
{
    ls_opts_t opts = {0,0,0,0};
    int i = 1;
    for (; i < argc; ++i) {
        if (argv[i][0] != '-' || strcmp(argv[i], "-") == 0)
            break;
        const char *p = argv[i] + 1;
        if (*p == '\0') break;
        for (; *p; ++p) {
            if (*p == 'a') opts.opt_a = 1;
            else if (*p == 'l') opts.opt_l = 1;
            else if (*p == 'R') opts.opt_R = 1;
            else if (*p == 't') opts.opt_t = 1;
            else { usage(argv[0]); return 84; }
        }
    }
    int npaths = argc - i;
    if (npaths <= 0) {
        char *def = ".";
        return list_paths(&def, 1, &opts);
    }
    return list_paths(&argv[i], npaths, &opts);
}

int main(int argc, char **argv)
{
    return run_ls(argc, argv);
}


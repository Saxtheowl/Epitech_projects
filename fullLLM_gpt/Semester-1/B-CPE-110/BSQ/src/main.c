#include <unistd.h>
#include "../include/bsq.h"

int run_bsq(const char *path);

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    return run_bsq(av[1]);
}


#include <stdlib.h>
#include "phoenix.h"

int main(int ac, char **av)
{
    char *str = concat_parameters(ac, av);

    if (!str) {
        return EXIT_FAILURE;
    }
    show_string(str);
    free(str);
    return EXIT_SUCCESS;
}

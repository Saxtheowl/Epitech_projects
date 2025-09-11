#include <stdlib.h>
#include "phoenix.h"

char *concat_parameters(int ac, char **av);

int main(int ac, char **av)
{
    char *str = concat_parameters(ac, av);
    show_string(str);
    free(str);
    return (EXIT_SUCCESS);
}
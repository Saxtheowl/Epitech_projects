#include <stdlib.h>
#include "infin_add.h"

int main(int ac, char **av)
{
    char *result;
    
    if (ac != 3)
        return 84;
    
    result = infin_add(av[1], av[2]);
    if (!result)
        return 84;
    
    my_putstr(result);
    my_putchar('\n');
    free(result);
    
    return 0;
}
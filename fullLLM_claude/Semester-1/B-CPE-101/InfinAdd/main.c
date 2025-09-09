#include "infin_add.h"

int main(int argc, char **argv)
{
    char *result;
    
    if (argc != 3)
        return 84;
    
    result = infin_add(argv[1], argv[2]);
    if (!result)
        return 84;
    
    my_putstr(result);
    write(1, "\n", 1);
    
    free(result);
    return 0;
}
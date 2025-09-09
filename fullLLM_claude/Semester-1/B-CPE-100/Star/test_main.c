#include <stdlib.h>

void star(unsigned int size);

int main(int argc, char **argv)
{
    unsigned int size;
    
    if (argc != 2)
        return 1;
    
    size = atoi(argv[1]);
    star(size);
    return 0;
}
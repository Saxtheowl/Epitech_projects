#include <stdlib.h>

void tree(int size);

int main(int argc, char **argv)
{
    int size;
    
    if (argc != 2)
        return 1;
    
    size = atoi(argv[1]);
    tree(size);
    return 0;
}
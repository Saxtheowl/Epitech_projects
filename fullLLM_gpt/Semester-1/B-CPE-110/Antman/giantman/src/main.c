#include <stdlib.h>
#include "../include/giantman.h"

int main(int argc, char **argv)
{
    if (argc != 3)
        return 84;
    int type = atoi(argv[2]);
    return decompress_file(argv[1], type);
}

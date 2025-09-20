#include <stdlib.h>
#include "../include/antman.h"

int main(int argc, char **argv)
{
    if (argc != 3)
        return 84;
    int type = atoi(argv[2]);
    return compress_file(argv[1], type);
}

#include <stdlib.h>
#include "phoenix.h"

int main(int argc, char **argv)
{
    for (int i = 0; i < argc; ++i) {
        show_string(argv[i]);
        my_putchar('\n');
    }
    return EXIT_SUCCESS;
}

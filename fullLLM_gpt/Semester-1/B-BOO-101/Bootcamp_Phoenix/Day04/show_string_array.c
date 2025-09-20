#include "phoenix.h"

int show_string_array(char *const *array)
{
    if (!array) {
        return 0;
    }
    for (int i = 0; array[i] != NULL; ++i) {
        show_string(array[i]);
        my_putchar('\n');
    }
    return 0;
}

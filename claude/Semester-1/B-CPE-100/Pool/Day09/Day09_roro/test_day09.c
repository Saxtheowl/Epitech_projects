#include <stdio.h>
#include <stdlib.h>
#include "my.h"

int main(int ac, char **av)
{
    struct info_param *params;
    int color;
    int swapped_color;

    printf("=== TEST Day09 Functions ===\n\n");

    printf("1. Testing my_params_to_array:\n");
    params = my_params_to_array(ac, av);
    if (params != NULL) {
        printf("Parameters successfully converted to array.\n");
        my_show_param_array(params);
        free(params);
    }

    printf("\n2. Testing get_color:\n");
    color = get_color(255, 128, 64);
    printf("get_color(255, 128, 64) = 0x%06X\n", color);

    printf("\n3. Testing swap_endian_color:\n");
    swapped_color = swap_endian_color(color);
    printf("swap_endian_color(0x%06X) = 0x%06X\n", color, swapped_color);

    printf("\n4. Testing ABS macro:\n");
    printf("ABS(-42) = %d\n", ABS(-42));
    printf("ABS(42) = %d\n", ABS(42));

    return 0;
}
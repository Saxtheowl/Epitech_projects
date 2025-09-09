#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"

char **create_test_world_1(void)
{
    char **world = malloc(sizeof(char*) * 4);
    world[0] = strdup("..X..");
    world[1] = strdup("..X..");
    world[2] = strdup(".....");
    world[3] = NULL;
    return world;
}

char **create_test_world_2(void)
{
    char **world = malloc(sizeof(char*) * 4);
    world[0] = strdup("X.X..");
    world[1] = strdup(".....");
    world[2] = strdup("..XX.");
    world[3] = NULL;
    return world;
}

char **create_test_world_3(void)
{
    char **world = malloc(sizeof(char*) * 4);
    world[0] = strdup("XXXX.");
    world[1] = strdup("X..X.");
    world[2] = strdup("XXXX.");
    world[3] = NULL;
    return world;
}

void free_world(char **world)
{
    int i = 0;
    while (world[i]) {
        free(world[i]);
        i++;
    }
    free(world);
}

void print_world(char **world)
{
    int i = 0;
    while (world[i]) {
        my_putstr(world[i]);
        my_putchar('\n');
        i++;
    }
}

int test_single_island(void)
{
    my_putstr("Test 1 - Single vertical island:\n");
    char **world = create_test_world_1();
    int result = count_island(world);
    print_world(world);
    my_putstr("Expected: 1, Got: ");
    my_put_nbr(result);
    my_putchar('\n');
    free_world(world);
    return (result == 1) ? 0 : 1;
}

int test_multiple_islands(void)
{
    my_putstr("\nTest 2 - Multiple islands:\n");
    char **world = create_test_world_2();
    int result = count_island(world);
    print_world(world);
    my_putstr("Expected: 3, Got: ");
    my_put_nbr(result);
    my_putchar('\n');
    free_world(world);
    return (result == 3) ? 0 : 1;
}

int test_connected_island(void)
{
    my_putstr("\nTest 3 - Large connected island:\n");
    char **world = create_test_world_3();
    int result = count_island(world);
    print_world(world);
    my_putstr("Expected: 1, Got: ");
    my_put_nbr(result);
    my_putchar('\n');
    free_world(world);
    return (result == 1) ? 0 : 1;
}

int main(void)
{
    int errors = 0;
    
    my_putstr("=== COUNT ISLAND TESTS ===\n");
    
    errors += test_single_island();
    errors += test_multiple_islands();
    errors += test_connected_island();
    
    my_putstr("\n=== RESULTS ===\n");
    if (errors == 0) {
        my_putstr("All tests PASSED!\n");
    } else {
        my_putstr("Some tests FAILED! Errors: ");
        my_put_nbr(errors);
        my_putchar('\n');
    }
    
    return errors;
}
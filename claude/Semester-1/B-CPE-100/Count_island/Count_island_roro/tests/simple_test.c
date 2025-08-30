/*
** EPITECH PROJECT, 2024
** simple_test.c
** File description:
** simple tests for count_island without external framework
*/

#include <stdlib.h>
#include "../include/count_island.h"

static char *create_test_line(char *content)
{
    int len = my_strlen(content);
    char *line = malloc(sizeof(char) * (len + 1));
    int i = 0;

    for (i = 0; i < len; i++)
        line[i] = content[i];
    line[i] = '\0';
    return line;
}

static void test_single_island(void)
{
    char **world = malloc(sizeof(char *) * 4);
    int result = 0;
    
    world[0] = create_test_line(".....");
    world[1] = create_test_line(".XXX.");
    world[2] = create_test_line(".....");
    world[3] = NULL;
    
    result = count_island(world);
    
    my_putstr("Test single island: ");
    if (result == 1 && world[1][1] == '0' && 
        world[1][2] == '0' && world[1][3] == '0') {
        my_putstr("PASS\n");
    } else {
        my_putstr("FAIL\n");
    }
    
    free(world[0]);
    free(world[1]);
    free(world[2]);
    free(world);
}

static void test_multiple_islands(void)
{
    char **world = malloc(sizeof(char *) * 4);
    int result = 0;
    
    world[0] = create_test_line("X.X");
    world[1] = create_test_line("...");
    world[2] = create_test_line(".X.");
    world[3] = NULL;
    
    result = count_island(world);
    
    my_putstr("Test multiple islands: ");
    if (result == 3 && world[0][0] == '0' && 
        world[0][2] == '1' && world[2][1] == '2') {
        my_putstr("PASS\n");
    } else {
        my_putstr("FAIL\n");
    }
    
    free(world[0]);
    free(world[1]);
    free(world[2]);
    free(world);
}

static void test_connected_island(void)
{
    char **world = malloc(sizeof(char *) * 4);
    int result = 0;
    
    world[0] = create_test_line(".X.");
    world[1] = create_test_line("XX.");
    world[2] = create_test_line(".X.");
    world[3] = NULL;
    
    result = count_island(world);
    
    my_putstr("Test connected island: ");
    if (result == 1 && world[0][1] == '0' && world[1][0] == '0' && 
        world[1][1] == '0' && world[2][1] == '0') {
        my_putstr("PASS\n");
    } else {
        my_putstr("FAIL\n");
    }
    
    free(world[0]);
    free(world[1]);
    free(world[2]);
    free(world);
}

int main(void)
{
    my_putstr("Running simple tests...\n");
    test_single_island();
    test_multiple_islands();
    test_connected_island();
    my_putstr("Tests completed.\n");
    return 0;
}
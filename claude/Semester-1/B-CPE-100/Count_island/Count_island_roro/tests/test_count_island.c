/*
** EPITECH PROJECT, 2024
** test_count_island.c
** File description:
** unit tests for count_island project
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
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

Test(count_island, test_empty_world)
{
    char **world = NULL;
    int result = count_island(world);
    
    cr_assert_eq(result, 0);
}

Test(count_island, test_world_with_null_terminator)
{
    char **world = malloc(sizeof(char *) * 1);
    
    world[0] = NULL;
    int result = count_island(world);
    
    cr_assert_eq(result, 0);
    free(world);
}

Test(count_island, test_single_island)
{
    char **world = malloc(sizeof(char *) * 4);
    
    world[0] = create_test_line(".....");
    world[1] = create_test_line(".XXX.");
    world[2] = create_test_line(".....");
    world[3] = NULL;
    
    int result = count_island(world);
    
    cr_assert_eq(result, 1);
    cr_assert_eq(world[1][1], '0');
    cr_assert_eq(world[1][2], '0');
    cr_assert_eq(world[1][3], '0');
    
    free(world[0]);
    free(world[1]);
    free(world[2]);
    free(world);
}

Test(count_island, test_multiple_islands)
{
    char **world = malloc(sizeof(char *) * 5);
    
    world[0] = create_test_line("X.X");
    world[1] = create_test_line("...");
    world[2] = create_test_line(".X.");
    world[3] = create_test_line("...");
    world[4] = NULL;
    
    int result = count_island(world);
    
    cr_assert_eq(result, 3);
    cr_assert_eq(world[0][0], '0');
    cr_assert_eq(world[0][2], '1');
    cr_assert_eq(world[2][1], '2');
    
    free(world[0]);
    free(world[1]);
    free(world[2]);
    free(world[3]);
    free(world);
}

Test(count_island, test_connected_island)
{
    char **world = malloc(sizeof(char *) * 4);
    
    world[0] = create_test_line(".X.");
    world[1] = create_test_line("XX.");
    world[2] = create_test_line(".X.");
    world[3] = NULL;
    
    int result = count_island(world);
    
    cr_assert_eq(result, 1);
    cr_assert_eq(world[0][1], '0');
    cr_assert_eq(world[1][0], '0');
    cr_assert_eq(world[1][1], '0');
    cr_assert_eq(world[2][1], '0');
    
    free(world[0]);
    free(world[1]);
    free(world[2]);
    free(world);
}

Test(count_island, test_no_islands)
{
    char **world = malloc(sizeof(char *) * 3);
    
    world[0] = create_test_line(".....");
    world[1] = create_test_line(".....");
    world[2] = NULL;
    
    int result = count_island(world);
    
    cr_assert_eq(result, 0);
    
    free(world[0]);
    free(world[1]);
    free(world);
}

Test(utils, test_get_grid_height)
{
    char **world = malloc(sizeof(char *) * 4);
    
    world[0] = create_test_line("test");
    world[1] = create_test_line("test");
    world[2] = create_test_line("test");
    world[3] = NULL;
    
    int height = get_grid_height(world);
    
    cr_assert_eq(height, 3);
    
    free(world[0]);
    free(world[1]);
    free(world[2]);
    free(world);
}

Test(utils, test_get_grid_width)
{
    char **world = malloc(sizeof(char *) * 2);
    
    world[0] = create_test_line("hello");
    world[1] = NULL;
    
    int width = get_grid_width(world, 0);
    
    cr_assert_eq(width, 5);
    
    free(world[0]);
    free(world);
}

Test(utils, test_is_valid_position)
{
    char **world = malloc(sizeof(char *) * 3);
    
    world[0] = create_test_line("hello");
    world[1] = create_test_line("world");
    world[2] = NULL;
    
    cr_assert_eq(is_valid_position(world, 0, 0), 1);
    cr_assert_eq(is_valid_position(world, 1, 4), 1);
    cr_assert_eq(is_valid_position(world, 2, 0), 0);
    cr_assert_eq(is_valid_position(world, 0, 5), 0);
    cr_assert_eq(is_valid_position(world, -1, 0), 0);
    cr_assert_eq(is_valid_position(world, 0, -1), 0);
    
    free(world[0]);
    free(world[1]);
    free(world);
}
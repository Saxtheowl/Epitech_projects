/*
** EPITECH PROJECT, 2024
** My_ls
** File description:
** Test program for my_ls functionality
*/

#include "../include/my_ls.h"
#include <stdio.h>
#include <assert.h>

void test_options_parsing(void)
{
    options_t opts;
    char *argv1[] = {"my_ls", "-al", "file"};
    char *argv2[] = {"my_ls", "-lRt", "dir"};
    char *argv3[] = {"my_ls", "-d", "-r", "path"};
    int result;

    printf("Testing option parsing...\n");
    
    opts = (options_t){0, 0, 0, 0, 0, 0};
    result = parse_options(3, argv1, &opts);
    assert(result == 2);
    assert(opts.a_flag == 1);
    assert(opts.l_flag == 1);
    
    opts = (options_t){0, 0, 0, 0, 0, 0};
    result = parse_options(3, argv2, &opts);
    assert(result == 2);
    assert(opts.l_flag == 1);
    assert(opts.R_flag == 1);
    assert(opts.t_flag == 1);
    
    opts = (options_t){0, 0, 0, 0, 0, 0};
    result = parse_options(4, argv3, &opts);
    assert(result == 3);
    assert(opts.d_flag == 1);
    assert(opts.r_flag == 1);
    
    printf("✓ Option parsing tests passed\n");
}

void test_string_functions(void)
{
    char dest[100];
    char *dup;
    
    printf("Testing string utility functions...\n");
    
    assert(my_strlen("hello") == 5);
    assert(my_strlen("") == 0);
    assert(my_strlen(NULL) == 0);
    
    assert(my_strcmp("abc", "abc") == 0);
    assert(my_strcmp("abc", "def") < 0);
    assert(my_strcmp("def", "abc") > 0);
    
    my_strcpy(dest, "test");
    assert(my_strcmp(dest, "test") == 0);
    
    my_strcpy(dest, "hello");
    my_strcat(dest, " world");
    assert(my_strcmp(dest, "hello world") == 0);
    
    dup = my_strdup("duplicate");
    assert(my_strcmp(dup, "duplicate") == 0);
    free(dup);
    
    printf("✓ String function tests passed\n");
}

void test_basic_ls(void)
{
    options_t opts = {0, 0, 0, 0, 0, 0};
    
    printf("Testing basic ls functionality...\n");
    
    printf("Testing current directory listing:\n");
    my_ls(&opts, NULL, 0);
    
    printf("\n✓ Basic ls functionality tested\n");
}

int main(void)
{
    printf("=== My_ls Test Suite ===\n\n");
    
    test_options_parsing();
    test_string_functions();
    test_basic_ls();
    
    printf("\n=== All tests completed successfully ===\n");
    return 0;
}
/*
** EPITECH PROJECT, 2024
** Minishell1
** File description:
** Test program for mysh functionality
*/

#include "../include/mysh.h"
#include <assert.h>

void test_utility_functions(void)
{
    char *str1, *str2;
    
    printf("Testing utility functions...\n");
    
    assert(my_strlen("hello") == 5);
    assert(my_strlen("") == 0);
    assert(my_strlen(NULL) == 0);
    
    assert(my_strcmp("abc", "abc") == 0);
    assert(my_strcmp("abc", "def") < 0);
    assert(my_strcmp("def", "abc") > 0);
    
    str1 = my_strdup("test");
    assert(str1 != NULL);
    assert(my_strcmp(str1, "test") == 0);
    free(str1);
    
    str2 = malloc(20);
    strcpy(str2, "hello");
    my_strcat(str2, " world");
    assert(my_strcmp(str2, "hello world") == 0);
    free(str2);
    
    printf("✓ Utility function tests passed\n");
}

void test_environment_management(void)
{
    shell_t shell;
    char *value;
    
    printf("Testing environment management...\n");
    
    shell.env_list = NULL;
    shell.environ_copy = NULL;
    shell.last_status = 0;
    shell.running = 1;
    
    add_env_var(&shell, "TEST_VAR", "test_value");
    value = get_env_var(&shell, "TEST_VAR");
    assert(value != NULL);
    assert(my_strcmp(value, "test_value") == 0);
    
    add_env_var(&shell, "TEST_VAR", "new_value");
    value = get_env_var(&shell, "TEST_VAR");
    assert(value != NULL);
    assert(my_strcmp(value, "new_value") == 0);
    
    remove_env_var(&shell, "TEST_VAR");
    value = get_env_var(&shell, "TEST_VAR");
    assert(value == NULL);
    
    cleanup_environment(&shell);
    
    printf("✓ Environment management tests passed\n");
}

void test_command_parsing(void)
{
    char **args;
    char command_line[] = "ls -l /tmp";
    
    printf("Testing command parsing...\n");
    
    args = parse_command(command_line);
    assert(args != NULL);
    assert(my_strcmp(args[0], "ls") == 0);
    assert(my_strcmp(args[1], "-l") == 0);
    assert(my_strcmp(args[2], "/tmp") == 0);
    assert(args[3] == NULL);
    
    free_args(args);
    
    args = parse_command("");
    assert(args == NULL);
    
    printf("✓ Command parsing tests passed\n");
}

void test_builtin_detection(void)
{
    printf("Testing builtin detection...\n");
    
    assert(is_builtin("cd") == 1);
    assert(is_builtin("env") == 1);
    assert(is_builtin("setenv") == 1);
    assert(is_builtin("unsetenv") == 1);
    assert(is_builtin("exit") == 1);
    assert(is_builtin("ls") == 0);
    assert(is_builtin("unknown") == 0);
    
    printf("✓ Builtin detection tests passed\n");
}

void test_builtin_commands(void)
{
    shell_t shell;
    char *args_setenv[] = {"setenv", "TEST", "value", NULL};
    char *args_unsetenv[] = {"unsetenv", "TEST", NULL};
    char *value;
    
    printf("Testing builtin commands...\n");
    
    shell.env_list = NULL;
    shell.environ_copy = NULL;
    shell.last_status = 0;
    shell.running = 1;
    
    assert(builtin_setenv(&shell, args_setenv) == 0);
    value = get_env_var(&shell, "TEST");
    assert(value != NULL);
    assert(my_strcmp(value, "value") == 0);
    
    assert(builtin_unsetenv(&shell, args_unsetenv) == 0);
    value = get_env_var(&shell, "TEST");
    assert(value == NULL);
    
    cleanup_environment(&shell);
    
    printf("✓ Builtin command tests passed\n");
}

int main(void)
{
    printf("=== Minishell1 Test Suite ===\n\n");
    
    test_utility_functions();
    test_environment_management();
    test_command_parsing();
    test_builtin_detection();
    test_builtin_commands();
    
    printf("\n=== All tests completed ===\n");
    return 0;
}
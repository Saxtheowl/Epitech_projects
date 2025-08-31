/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Basic test suite for enhanced minishell
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Minishell2 Test Suite\n");
    printf("====================\n\n");

    printf("Testing basic functionality:\n");
    printf("1. Semicolon separation: ls; pwd\n");
    printf("2. Pipe operations: ls | wc -l\n");
    printf("3. Output redirection: echo hello > output.txt\n");
    printf("4. Input redirection: cat < output.txt\n");
    printf("5. Append redirection: echo world >> output.txt\n");
    printf("6. Complex pipeline: ls -l | grep test | wc -l\n");

    return 0;
}
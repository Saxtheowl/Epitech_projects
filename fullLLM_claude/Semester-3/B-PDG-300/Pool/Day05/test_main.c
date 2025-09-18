/*
** EPITECH PROJECT, 2024
** Day05 PDG - test_main.c
** File description:
** Simple test for string_t module
*/

#include <stdio.h>
#include "include/my_string.h"

int main(void)
{
    string_t s;
    
    printf("Testing string_init and string_destroy...\n");
    
    // Test with normal string
    string_init(&s, "Hello World");
    printf("Initialized string: %s\n", s.str ? s.str : "NULL");
    string_destroy(&s);
    printf("After destroy, str pointer: %s\n", s.str ? s.str : "NULL");
    
    // Test with NULL string
    string_init(&s, NULL);
    printf("Initialized with NULL: %s\n", s.str ? s.str : "NULL");
    string_destroy(&s);
    
    // Test with empty string
    string_init(&s, "");
    printf("Initialized with empty string: '%s'\n", s.str ? s.str : "NULL");
    string_destroy(&s);
    
    printf("All tests completed!\n");
    return (0);
}
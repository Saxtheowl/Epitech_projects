/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** Main function for Organized workshop management system
*/

#include "../include/organized.h"
#include "../include/shell.h"
#include <stdlib.h>

int main(void)
{
    workshop_t *workshop;
    int result;

    workshop = workshop_create();
    if (!workshop)
        return EXIT_ERROR;
    
    result = workshop_shell(workshop);
    
    workshop_free(workshop);
    
    return (result == EXIT_SUCCESS) ? EXIT_SUCCESS : EXIT_ERROR;
}
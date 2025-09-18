/*
** EPITECH PROJECT, 2024
** Day05 PDG - string_destroy.c
** File description:
** Destroy/cleanup string_t structure
*/

#include <stdlib.h>
#include "../include/my_string.h"

void string_destroy(string_t *this)
{
    if (this == NULL) {
        return;
    }
    
    if (this->str != NULL) {
        free(this->str);
        this->str = NULL;
    }
}
/*
** EPITECH PROJECT, 2024
** Day05 PDG - string_init.c
** File description:
** Initialize string_t structure
*/

#include <stdlib.h>
#include <string.h>
#include "../include/my_string.h"

void string_init(string_t *this, const char *s)
{
    if (this == NULL) {
        return;
    }
    
    if (s == NULL) {
        this->str = NULL;
        return;
    }
    
    this->str = malloc(sizeof(char) * (strlen(s) + 1));
    if (this->str == NULL) {
        return;
    }
    
    strcpy(this->str, s);
}
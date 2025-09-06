/*
** EPITECH PROJECT, 2025
** Day05 - String Module
** File description:
** String initialization function
*/

#include "string.h"

void string_init(string_t *this, const char *s)
{
    if (!this || !s) {
        if (this)
            this->str = NULL;
        return;
    }

    this->str = malloc(strlen(s) + 1);
    if (!this->str)
        return;

    strcpy(this->str, s);
}
/*
** EPITECH PROJECT, 2025
** Day05 - String Module
** File description:
** String destruction function
*/

#include "string.h"

void string_destroy(string_t *this)
{
    if (!this)
        return;

    if (this->str) {
        free(this->str);
        this->str = NULL;
    }
}
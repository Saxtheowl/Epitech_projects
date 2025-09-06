/*
** EPITECH PROJECT, 2025
** Day05 - String Module
** File description:
** Header file for string module
*/

#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct string_s {
    char *str;
} string_t;

void string_init(string_t *this, const char *s);
void string_destroy(string_t *this);
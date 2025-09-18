/*
** EPITECH PROJECT, 2024
** Day05 PDG - string.h
** File description:
** Header file for string_t module
*/

#ifndef MY_STRING_H_
#define MY_STRING_H_

#include <stdlib.h>

typedef struct {
    char *str;
} string_t;

void string_init(string_t *this, const char *s);
void string_destroy(string_t *this);

#endif /* !MY_STRING_H_ */
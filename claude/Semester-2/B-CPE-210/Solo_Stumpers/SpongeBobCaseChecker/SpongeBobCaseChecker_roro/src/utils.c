/*
** EPITECH PROJECT, 2025
** SpongeBobCaseChecker
** File description:
** Utility functions for spongebob_case_checker
*/

#include "spongebob_case_checker.h"

int is_letter(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int is_upper(char c)
{
    return (c >= 'A' && c <= 'Z');
}

int is_lower(char c)
{
    return (c >= 'a' && c <= 'z');
}

void print_ok(void)
{
    write(1, "OK\n", 3);
}

void print_invalid(void)
{
    write(1, "Invalid\n", 8);
}
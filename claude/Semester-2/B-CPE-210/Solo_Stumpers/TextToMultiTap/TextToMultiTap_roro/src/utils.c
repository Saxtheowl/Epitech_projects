/*
** EPITECH PROJECT, 2025
** TextToMultiTap
** File description:
** Utility functions for text_to_multi_tap
*/

#include "text_to_multi_tap.h"

int get_key_for_char(char c)
{
    if (c >= 'a' && c <= 'c') return 2;
    if (c >= 'd' && c <= 'f') return 3;
    if (c >= 'g' && c <= 'i') return 4;
    if (c >= 'j' && c <= 'l') return 5;
    if (c >= 'm' && c <= 'o') return 6;
    if (c >= 'p' && c <= 's') return 7;
    if (c >= 't' && c <= 'v') return 8;
    if (c >= 'w' && c <= 'z') return 9;
    if (c == ' ') return 0;
    return -1;
}

int get_press_count(char c)
{
    if (c == ' ') return 1;
    if (c == 'a') return 1;
    if (c == 'b') return 2;
    if (c == 'c') return 3;
    if (c == 'd') return 1;
    if (c == 'e') return 2;
    if (c == 'f') return 3;
    if (c == 'g') return 1;
    if (c == 'h') return 2;
    if (c == 'i') return 3;
    if (c == 'j') return 1;
    if (c == 'k') return 2;
    if (c == 'l') return 3;
    if (c == 'm') return 1;
    if (c == 'n') return 2;
    if (c == 'o') return 3;
    if (c == 'p') return 1;
    if (c == 'q') return 2;
    if (c == 'r') return 3;
    if (c == 's') return 4;
    if (c == 't') return 1;
    if (c == 'u') return 2;
    if (c == 'v') return 3;
    if (c == 'w') return 1;
    if (c == 'x') return 2;
    if (c == 'y') return 3;
    if (c == 'z') return 4;
    return -1;
}
/*
** EPITECH PROJECT, 2024
** Day09 - B-CPE-100
** File description:
** get_color.c - TASK 05
*/

int get_color(unsigned char red, unsigned char green, unsigned char blue)
{
    int color = 0;
    
    color |= (int)red << 16;    // Red component in bits 16-23
    color |= (int)green << 8;   // Green component in bits 8-15
    color |= (int)blue;         // Blue component in bits 0-7
    
    return color;
}
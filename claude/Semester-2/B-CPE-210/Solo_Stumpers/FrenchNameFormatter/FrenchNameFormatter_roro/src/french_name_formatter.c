/*
** EPITECH PROJECT, 2025
** FrenchNameFormatter
** File description:
** French name formatter implementation
*/

#include <unistd.h>
#include <stdio.h>

char to_upper(char c) {
    if (c >= 'a' && c <= 'z') return c - 32;
    return c;
}

char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32;
    return c;
}

int main(int argc, char **argv) {
    int i;
    
    if (argc != 3) return 84;
    
    // Last name: all uppercase
    for (i = 0; argv[2][i]; i++)
        printf("%c", to_upper(argv[2][i]));
    
    printf(", ");
    
    // First name: capitalize first letter, rest lowercase
    printf("%c", to_upper(argv[1][0]));
    for (i = 1; argv[1][i]; i++)
        printf("%c", to_lower(argv[1][i]));
    
    printf("\n");
    return 0;
}
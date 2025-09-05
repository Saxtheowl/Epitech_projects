/*
** EPITECH PROJECT, 2025
** GpaCalculator
** File description:
** GPA calculator implementation
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    float total = 0, count = 0, grade;
    int i;
    
    if (argc < 2) return 84;
    
    for (i = 1; i < argc; i++) {
        grade = atof(argv[i]);
        if (grade < 0 || grade > 20) return 84;
        total += grade;
        count++;
    }
    
    printf("%.2f\n", total / count);
    return 0;
}
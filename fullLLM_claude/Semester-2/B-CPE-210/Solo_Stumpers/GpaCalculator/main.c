/*
** EPITECH PROJECT, 2024
** GPA Calculator
** File description:
** Calculate Grade Point Average from grades and credits
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_grade_points(char grade)
{
    switch (grade) {
        case 'A':
            return 4;
        case 'B':
            return 3;
        case 'C':
            return 2;
        case 'D':
            return 1;
        case 'E':
            return 0;
        default:
            return -1;
    }
}

int parse_grade_credit(char *arg, int *grade_points, int *credits)
{
    char *token;
    char *arg_copy;
    char grade;
    
    arg_copy = malloc(strlen(arg) + 1);
    if (!arg_copy)
        return 0;
    
    strcpy(arg_copy, arg);
    
    token = strtok(arg_copy, ",");
    if (!token || strlen(token) != 1) {
        free(arg_copy);
        return 0;
    }
    
    grade = token[0];
    *grade_points = get_grade_points(grade);
    if (*grade_points == -1) {
        free(arg_copy);
        return 0;
    }
    
    token = strtok(NULL, ",");
    if (!token) {
        free(arg_copy);
        return 0;
    }
    
    *credits = atoi(token);
    if (*credits <= 0) {
        free(arg_copy);
        return 0;
    }
    
    free(arg_copy);
    return 1;
}

double calculate_gpa(int argc, char **argv)
{
    int i;
    int grade_points, credits;
    int total_weighted_points = 0;
    int total_credits = 0;
    
    for (i = 1; i < argc; i++) {
        if (!parse_grade_credit(argv[i], &grade_points, &credits)) {
            return -1.0;
        }
        
        total_weighted_points += grade_points * credits;
        total_credits += credits;
    }
    
    if (total_credits == 0)
        return 0.0;
    
    return (double)total_weighted_points / (double)total_credits;
}

int main(int argc, char **argv)
{
    double gpa;
    
    if (argc < 2) {
        return 84;
    }
    
    gpa = calculate_gpa(argc, argv);
    if (gpa < 0) {
        return 84;
    }
    
    printf("%.2f\n", gpa);
    
    return 0;
}
/*
** EPITECH PROJECT, 2025
** SpongeBobCaseChecker
** File description:
** Header file for spongebob_case_checker project
*/

#ifndef SPONGEBOB_CASE_CHECKER_H_
    #define SPONGEBOB_CASE_CHECKER_H_

    #include <unistd.h>

// Main function
int check_spongebob_case(char *str);

// Utility functions
int is_letter(char c);
int is_upper(char c);
int is_lower(char c);
void print_ok(void);
void print_invalid(void);

#endif /* !SPONGEBOB_CASE_CHECKER_H_ */
/*
** EPITECH PROJECT, 2025
** TextToMultiTap
** File description:
** Header file for text_to_multi_tap project
*/

#ifndef TEXT_TO_MULTI_TAP_H_
    #define TEXT_TO_MULTI_TAP_H_

    #include <unistd.h>

// Main function
int text_to_multi_tap(char *str);

// Utility functions
int get_key_for_char(char c);
int get_press_count(char c);
int is_valid_char(char c);
void write_char(char c);
void write_str(char *str);
char to_lower(char c);
char to_upper(char c);
int is_upper(char c);

#endif /* !TEXT_TO_MULTI_TAP_H_ */
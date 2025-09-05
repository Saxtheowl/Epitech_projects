/*
** EPITECH PROJECT, 2025
** GeekNameFormatter
** File description:
** Header file for geek name formatter
*/

#ifndef GEEK_NAME_FORMATTER_H_
    #define GEEK_NAME_FORMATTER_H_

    #include <unistd.h>

    #define SUCCESS 0
    #define ERROR 84

void my_putstr(char *str);
void my_putchar(char c);
int my_strlen(char *str);
char replace_geek_char(char c);
char to_upper(char c);
char to_lower(char c);
void format_geek_name(char *name);

#endif /* !GEEK_NAME_FORMATTER_H_ */
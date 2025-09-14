/*
** EPITECH PROJECT, 2024
** Spongebob Case Checker
** File description:
** Check if a string follows spongebob case pattern
*/

#include <unistd.h>

void my_putstr(char *str)
{
    int i = 0;
    
    while (str[i]) {
        write(1, &str[i], 1);
        i++;
    }
}

int is_letter(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int is_uppercase(char c)
{
    return (c >= 'A' && c <= 'Z');
}

int is_lowercase(char c)
{
    return (c >= 'a' && c <= 'z');
}

int check_spongebob_case(char *str)
{
    int i = 0;
    int consecutive_count = 0;
    int last_case = -1; // -1 = no letters yet, 0 = lowercase, 1 = uppercase
    
    while (str[i]) {
        if (is_letter(str[i])) {
            int current_case = is_uppercase(str[i]) ? 1 : 0;
            
            if (last_case == -1 || current_case != last_case) {
                consecutive_count = 1;
            } else {
                consecutive_count++;
            }
            
            if (consecutive_count > 3) {
                return 0;
            }
            
            last_case = current_case;
        }
        i++;
    }
    
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        return 84;
    }
    
    if (check_spongebob_case(argv[1])) {
        my_putstr("OK\n");
    } else {
        my_putstr("Invalid\n");
    }
    
    return 0;
}
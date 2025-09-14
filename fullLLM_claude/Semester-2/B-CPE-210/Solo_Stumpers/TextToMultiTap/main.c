/*
** EPITECH PROJECT, 2024
** Text to Multi Tap
** File description:
** Convert text to old phone multi-tap keystrokes
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char *str)
{
    int i = 0;
    
    while (str[i]) {
        my_putchar(str[i]);
        i++;
    }
}

char *get_multitap_key(char c, int *key_num)
{
    if (c == ' ') {
        *key_num = 0;
        return "0";
    }
    if (c >= 'a' && c <= 'c') {
        *key_num = 2;
        return "222";
    }
    if (c >= 'd' && c <= 'f') {
        *key_num = 3;
        return "333";
    }
    if (c >= 'g' && c <= 'i') {
        *key_num = 4;
        return "444";
    }
    if (c >= 'j' && c <= 'l') {
        *key_num = 5;
        return "555";
    }
    if (c >= 'm' && c <= 'o') {
        *key_num = 6;
        return "666";
    }
    if (c >= 'p' && c <= 's') {
        *key_num = 7;
        return "7777";
    }
    if (c >= 't' && c <= 'v') {
        *key_num = 8;
        return "888";
    }
    if (c >= 'w' && c <= 'z') {
        *key_num = 9;
        return "9999";
    }
    
    *key_num = -1;
    return NULL;
}

char *get_multitap_sequence(char c, int *key_num)
{
    char *base_seq = get_multitap_key(c, key_num);
    int presses;
    
    if (!base_seq)
        return NULL;
    
    if (c == ' ') {
        return "0";
    }
    
    // Calculate number of presses based on position in key
    if (*key_num == 2) presses = (c - 'a') + 1;        // abc
    else if (*key_num == 3) presses = (c - 'd') + 1;   // def
    else if (*key_num == 4) presses = (c - 'g') + 1;   // ghi
    else if (*key_num == 5) presses = (c - 'j') + 1;   // jkl
    else if (*key_num == 6) presses = (c - 'm') + 1;   // mno
    else if (*key_num == 7) presses = (c - 'p') + 1;   // pqrs
    else if (*key_num == 8) presses = (c - 't') + 1;   // tuv
    else if (*key_num == 9) presses = (c - 'w') + 1;   // wxyz
    else presses = 1;
    
    return base_seq + (3 - presses); // Return substring with correct number of digits
}

char to_lowercase(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}

int is_uppercase(char c)
{
    return (c >= 'A' && c <= 'Z');
}

int convert_to_multitap(char *str)
{
    int i = 0;
    int prev_key = -1;
    int current_key;
    char *sequence;
    char current_char;
    int is_first = 1;
    
    while (str[i]) {
        current_char = to_lowercase(str[i]);
        
        if (is_uppercase(str[i]) && str[i] != ' ') {
            // Check if we need a space before # (if previous was same key as current uppercase letter)
            if (!is_first && get_multitap_sequence(current_char, &current_key) && current_key == prev_key && prev_key != 0 && prev_key != -1) {
                my_putchar(' ');
                prev_key = -1; // Reset to avoid double spacing later
            }
            my_putchar('#');
        }
        
        sequence = get_multitap_sequence(current_char, &current_key);
        if (!sequence) {
            return 0; // Invalid character
        }
        
        // Check if we need a space (same key as previous)
        if (!is_first && current_key == prev_key && prev_key != 0 && prev_key != -1) {
            my_putchar(' ');
        }
        
        my_putstr(sequence);
        prev_key = current_key;
        is_first = 0;
        i++;
    }
    
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        return 84;
    }
    
    if (!convert_to_multitap(argv[1])) {
        return 84;
    }
    
    my_putchar('\n');
    return 0;
}
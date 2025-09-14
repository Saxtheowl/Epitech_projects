/*
** EPITECH PROJECT, 2024
** Fractals
** File description:
** Fractal generation program
*/

#include <stdlib.h>
#include <unistd.h>

int my_strlen(char *str)
{
    int len = 0;
    
    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

int my_atoi(char *str)
{
    int result = 0;
    int i = 0;
    
    if (!str)
        return -1;
    if (str[0] == '-')
        return -1;
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return -1;
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

void my_putstr(char *str)
{
    if (str)
        write(1, str, my_strlen(str));
}

void my_putstr_error(char *str)
{
    if (str)
        write(2, str, my_strlen(str));
}

int validate_patterns(char *pattern1, char *pattern2)
{
    int len1 = my_strlen(pattern1);
    int len2 = my_strlen(pattern2);
    int i;
    int breaks1 = 0, breaks2 = 0;
    
    if (len1 != len2)
        return 0;
    
    for (i = 0; i < len1; i++) {
        if (pattern1[i] == '@')
            breaks1++;
        if (pattern2[i] == '@')
            breaks2++;
        if (pattern1[i] != '@' && pattern1[i] != '#' && pattern1[i] != '.')
            return 0;
        if (pattern2[i] != '@' && pattern2[i] != '#' && pattern2[i] != '.')
            return 0;
    }
    
    return (breaks1 == breaks2);
}

char *apply_transformation(char *current, char *hash_pattern, char *dot_pattern)
{
    int current_len = my_strlen(current);
    int pattern_len = my_strlen(hash_pattern);
    int new_size = current_len * pattern_len * 2;
    char *result = malloc(new_size);
    int result_pos = 0;
    int i, j;
    
    if (!result)
        return NULL;
    
    for (i = 0; i < current_len; i++) {
        if (current[i] == '#') {
            for (j = 0; j < pattern_len; j++) {
                if (hash_pattern[j] == '@')
                    result[result_pos++] = '\n';
                else
                    result[result_pos++] = hash_pattern[j];
            }
        } else if (current[i] == '.') {
            for (j = 0; j < pattern_len; j++) {
                if (dot_pattern[j] == '@')
                    result[result_pos++] = '\n';
                else
                    result[result_pos++] = dot_pattern[j];
            }
        }
    }
    
    result[result_pos] = '\0';
    return result;
}

int main(int argc, char **argv)
{
    int iterations;
    char *current;
    char *next;
    int i;
    
    if (argc != 4) {
        my_putstr_error("Usage: ./fractals iterations hash_pattern dot_pattern\n");
        return 84;
    }
    
    iterations = my_atoi(argv[1]);
    if (iterations < 0) {
        my_putstr_error("Invalid number of iterations\n");
        return 84;
    }
    
    if (!validate_patterns(argv[2], argv[3])) {
        my_putstr_error("Invalid patterns\n");
        return 84;
    }
    
    current = malloc(2);
    if (!current)
        return 84;
    current[0] = '#';
    current[1] = '\0';
    
    for (i = 0; i < iterations; i++) {
        next = apply_transformation(current, argv[2], argv[3]);
        if (!next) {
            free(current);
            return 84;
        }
        free(current);
        current = next;
    }
    
    my_putstr(current);
    write(1, "\n", 1);
    
    free(current);
    return 0;
}
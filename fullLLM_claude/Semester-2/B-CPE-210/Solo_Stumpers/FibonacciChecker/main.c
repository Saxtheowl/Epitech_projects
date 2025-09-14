/*
** EPITECH PROJECT, 2024
** Fibonacci Checker
** File description:
** Check if a sequence of numbers is a valid Fibonacci sequence
*/

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

void my_putstr(char *str)
{
    int i = 0;
    
    while (str[i]) {
        write(1, &str[i], 1);
        i++;
    }
}

void my_puterr(char *str)
{
    int len = 0;
    
    while (str[len])
        len++;
    write(2, str, len);
}

int my_strlen(char *str)
{
    int len = 0;
    
    while (str[len])
        len++;
    return len;
}

int is_valid_number(char *str)
{
    int i = 0;
    
    if (!str || str[0] == '\0')
        return 0;
    
    if (str[0] == '-' || str[0] == '+')
        i++;
    
    if (str[i] == '\0')
        return 0;
    
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    
    return 1;
}

long my_atol(char *str)
{
    long result = 0;
    int sign = 1;
    int i = 0;
    
    if (str[0] == '-') {
        sign = -1;
        i++;
    } else if (str[0] == '+') {
        i++;
    }
    
    while (str[i] >= '0' && str[i] <= '9') {
        if (result > (LONG_MAX - (str[i] - '0')) / 10) {
            return (sign == 1) ? LONG_MAX : LONG_MIN;
        }
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return result * sign;
}

int is_fibonacci_sequence(int *numbers, int count)
{
    int i;
    
    if (count < 3)
        return 0;
    
    for (i = 2; i < count; i++) {
        if (numbers[i] != numbers[i-1] + numbers[i-2])
            return 0;
    }
    
    return 1;
}

int main(int argc, char **argv)
{
    int i;
    int *numbers;
    long temp;
    
    if (argc < 4) {
        return 84;
    }
    
    numbers = malloc(sizeof(int) * (argc - 1));
    if (!numbers)
        return 84;
    
    for (i = 1; i < argc; i++) {
        if (!is_valid_number(argv[i])) {
            free(numbers);
            return 84;
        }
        
        temp = my_atol(argv[i]);
        if (temp > INT_MAX || temp < INT_MIN) {
            free(numbers);
            return 84;
        }
        
        numbers[i-1] = (int)temp;
    }
    
    if (is_fibonacci_sequence(numbers, argc - 1)) {
        my_putstr("OK\n");
        free(numbers);
        return 0;
    } else {
        my_putstr("Not a Fibonacci sequence\n");
        free(numbers);
        return 1;
    }
}
/*
** EPITECH PROJECT, 2025
** FibonacciChecker
** File description:
** Fibonacci checker implementation
*/

#include <unistd.h>
#include <stdlib.h>

void write_str(char *str) {
    int i = 0;
    while (str[i]) {
        write(1, &str[i], 1);
        i++;
    }
}

int main(int argc, char **argv) {
    int i, a, b, c;
    
    if (argc < 4) return 84;
    
    for (i = 1; i < argc; i++) {
        int j = 0, negative = 0, num = 0;
        if (argv[i][j] == '-') {
            negative = 1;
            j++;
        }
        while (argv[i][j]) {
            if (argv[i][j] < '0' || argv[i][j] > '9') return 84;
            num = num * 10 + (argv[i][j] - '0');
            j++;
        }
        if (negative) num = -num;
        
        if (i == 1) a = num;
        else if (i == 2) b = num;
        else {
            c = a + b;
            if (c != num) {
                write_str("Not a Fibonacci sequence\n");
                return 1;
            }
            a = b;
            b = c;
        }
    }
    
    write_str("OK\n");
    return 0;
}
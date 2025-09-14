#include <string.h>
#include <stdio.h>

extern int strncmp(const char *s1, const char *s2, size_t n);

int main() {
    printf("Standard strncmp(\"hello\", \"help\", 3) = %d\n", strncmp("hello", "help", 3));
    printf("Standard strncmp(\"hello\", \"help\", 5) = %d\n", strncmp("hello", "help", 5));
    printf("Our strncmp(\"hello\", \"help\", 3) = %d\n", strncmp("hello", "help", 3));
    printf("Our strncmp(\"hello\", \"help\", 5) = %d\n", strncmp("hello", "help", 5));
    return 0;
}
/*
** EPITECH PROJECT, 2025
** MiniLibC
** File description:
** Test file for MiniLibC functions
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>

// Forward declarations for our functions
size_t strlen(const char *s);
char *strchr(const char *s, int c);
void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
int strcmp(const char *s1, const char *s2);
void *memmove(void *dest, const void *src, size_t n);
int strncmp(const char *s1, const char *s2, size_t n);
int strcasecmp(const char *s1, const char *s2);
char *rindex(const char *s, int c);
char *strstr(const char *haystack, const char *needle);
char *strpbrk(const char *s, const char *accept);
size_t strcspn(const char *s, const char *reject);

int test_strlen(void)
{
    printf("Testing strlen...\n");
    
    // Test empty string
    if (strlen("") != 0) {
        printf("FAIL: strlen(\"\") should return 0\n");
        return 1;
    }
    
    // Test normal string
    if (strlen("hello") != 5) {
        printf("FAIL: strlen(\"hello\") should return 5\n");
        return 1;
    }
    
    // Test longer string
    if (strlen("Hello, World!") != 13) {
        printf("FAIL: strlen(\"Hello, World!\") should return 13\n");
        return 1;
    }
    
    printf("strlen tests passed!\n");
    return 0;
}

int test_strcmp(void)
{
    printf("Testing strcmp...\n");
    
    // Test equal strings
    if (strcmp("hello", "hello") != 0) {
        printf("FAIL: strcmp(\"hello\", \"hello\") should return 0\n");
        return 1;
    }
    
    // Test different strings
    int result = strcmp("abc", "abd");
    if (result >= 0) {
        printf("FAIL: strcmp(\"abc\", \"abd\") should return negative value\n");
        return 1;
    }
    
    result = strcmp("abd", "abc");
    if (result <= 0) {
        printf("FAIL: strcmp(\"abd\", \"abc\") should return positive value\n");
        return 1;
    }
    
    printf("strcmp tests passed!\n");
    return 0;
}

int test_strchr(void)
{
    printf("Testing strchr...\n");
    
    const char *str = "hello world";
    char *result;
    
    // Test finding existing character
    result = strchr(str, 'o');
    if (result != str + 4) {
        printf("FAIL: strchr should find first 'o' at position 4\n");
        return 1;
    }
    
    // Test finding non-existing character
    result = strchr(str, 'z');
    if (result != NULL) {
        printf("FAIL: strchr should return NULL for non-existing character\n");
        return 1;
    }
    
    printf("strchr tests passed!\n");
    return 0;
}

int main(void)
{
    printf("Running MiniLibC tests...\n\n");
    
    int failures = 0;
    
    failures += test_strlen();
    failures += test_strcmp();
    failures += test_strchr();
    
    if (failures == 0) {
        printf("\nAll tests passed!\n");
        return 0;
    } else {
        printf("\n%d test(s) failed!\n", failures);
        return 1;
    }
}
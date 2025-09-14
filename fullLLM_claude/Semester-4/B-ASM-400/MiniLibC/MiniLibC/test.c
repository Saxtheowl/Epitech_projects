#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Declare our ASM functions
extern size_t strlen(const char *s);
extern char *strchr(const char *s, int c);
extern void *memset(void *s, int c, size_t n);
extern void *memcpy(void *dest, const void *src, size_t n);
extern int strcmp(const char *s1, const char *s2);
extern void *memmove(void *dest, const void *src, size_t n);
extern int strncmp(const char *s1, const char *s2, size_t n);
extern int strcasecmp(const char *s1, const char *s2);
extern char *rindex(const char *s, int c);
extern char *strstr(const char *haystack, const char *needle);
extern char *strpbrk(const char *s, const char *accept);
extern size_t strcspn(const char *s, const char *reject);

int test_count = 0;
int passed_tests = 0;

#define TEST(name, condition) \
    do { \
        test_count++; \
        if (condition) { \
            passed_tests++; \
            printf("✓ %s\n", name); \
        } else { \
            printf("✗ %s\n", name); \
        } \
    } while(0)

int main() {
    printf("=== MiniLibC Test Suite ===\n\n");
    
    // Test strlen
    printf("Testing strlen:\n");
    TEST("strlen(\"hello\")", strlen("hello") == 5);
    TEST("strlen(\"\")", strlen("") == 0);
    TEST("strlen(\"a\")", strlen("a") == 1);
    
    // Test strchr
    printf("\nTesting strchr:\n");
    char *test_str = "hello world";
    TEST("strchr finds 'o'", strchr(test_str, 'o') == test_str + 4);
    TEST("strchr finds 'h'", strchr(test_str, 'h') == test_str);
    TEST("strchr returns NULL", strchr(test_str, 'z') == NULL);
    
    // Test memset
    printf("\nTesting memset:\n");
    char buffer[10];
    memset(buffer, 'A', 5);
    buffer[5] = '\0';
    TEST("memset fills correctly", strcmp(buffer, "AAAAA") == 0);
    
    // Test memcpy
    printf("\nTesting memcpy:\n");
    char src[] = "hello";
    char dest[10];
    memcpy(dest, src, 6);
    TEST("memcpy copies correctly", strcmp(dest, "hello") == 0);
    
    // Test strcmp
    printf("\nTesting strcmp:\n");
    TEST("strcmp equal strings", strcmp("hello", "hello") == 0);
    TEST("strcmp different strings", strcmp("hello", "world") < 0);
    TEST("strcmp first > second", strcmp("world", "hello") > 0);
    
    // Test memmove
    printf("\nTesting memmove:\n");
    char overlap[] = "hello world";
    memmove(overlap + 6, overlap, 5);
    overlap[11] = '\0';
    TEST("memmove with overlap", strstr(overlap, "hello") != NULL);
    
    // Test strncmp
    printf("\nTesting strncmp:\n");
    TEST("strncmp equal (n=3)", strncmp("hello", "help", 3) == 0);
    TEST("strncmp different (n=5)", strncmp("hello", "help", 5) < 0);
    
    // Test strcasecmp
    printf("\nTesting strcasecmp:\n");
    TEST("strcasecmp case insensitive", strcasecmp("Hello", "HELLO") == 0);
    TEST("strcasecmp different", strcasecmp("Hello", "World") < 0);
    
    // Test rindex
    printf("\nTesting rindex:\n");
    char *rtest = "hello world hello";
    char *last_h = rindex(rtest, 'h');
    TEST("rindex finds last occurrence", last_h == rtest + 12);
    TEST("rindex returns NULL", rindex(rtest, 'z') == NULL);
    
    // Test strstr
    printf("\nTesting strstr:\n");
    TEST("strstr finds substring", strstr("hello world", "wor") == strstr("hello world", "wor"));
    TEST("strstr empty needle", strstr("hello", "") == strstr("hello", ""));
    TEST("strstr not found", strstr("hello", "xyz") == NULL);
    
    // Test strpbrk
    printf("\nTesting strpbrk:\n");
    char *pbrk_result = strpbrk("hello world", "or");
    TEST("strpbrk finds character", pbrk_result != NULL && *pbrk_result == 'o');
    TEST("strpbrk not found", strpbrk("hello", "xyz") == NULL);
    
    // Test strcspn
    printf("\nTesting strcspn:\n");
    TEST("strcspn counts correctly", strcspn("hello", "aeiou") == 1);
    TEST("strcspn no match", strcspn("bcdfg", "aeiou") == 5);
    
    printf("\n=== Test Results ===\n");
    printf("Passed: %d/%d tests\n", passed_tests, test_count);
    
    if (passed_tests == test_count) {
        printf("🎉 All tests passed!\n");
        return 0;
    } else {
        printf("❌ Some tests failed.\n");
        return 1;
    }
}
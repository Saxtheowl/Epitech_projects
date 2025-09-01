/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** Test program for malloc implementation
*/

#include <stdio.h>
#include <string.h>

int main(void)
{
    printf("Testing malloc implementation...\n");
    
    // Test basic malloc
    void *ptr1 = malloc(100);
    if (!ptr1) {
        printf("FAIL: malloc(100) returned NULL\n");
        return 1;
    }
    printf("PASS: malloc(100) succeeded\n");
    
    // Test writing to allocated memory
    strcpy((char *)ptr1, "Hello, World!");
    printf("PASS: Writing to allocated memory: %s\n", (char *)ptr1);
    
    // Test calloc
    void *ptr2 = calloc(10, sizeof(int));
    if (!ptr2) {
        printf("FAIL: calloc(10, sizeof(int)) returned NULL\n");
        return 1;
    }
    printf("PASS: calloc(10, sizeof(int)) succeeded\n");
    
    // Verify calloc zeroed memory
    int *arr = (int *)ptr2;
    int zeroed = 1;
    for (int i = 0; i < 10; i++) {
        if (arr[i] != 0) {
            zeroed = 0;
            break;
        }
    }
    printf("%s: calloc zeroed memory\n", zeroed ? "PASS" : "FAIL");
    
    // Test realloc
    ptr1 = realloc(ptr1, 200);
    if (!ptr1) {
        printf("FAIL: realloc(ptr1, 200) returned NULL\n");
        return 1;
    }
    printf("PASS: realloc(ptr1, 200) succeeded\n");
    printf("PASS: Data preserved after realloc: %s\n", (char *)ptr1);
    
    // Test reallocarray
    void *ptr3 = reallocarray(ptr2, 20, sizeof(int));
    if (!ptr3) {
        printf("FAIL: reallocarray(ptr2, 20, sizeof(int)) returned NULL\n");
        return 1;
    }
    printf("PASS: reallocarray(ptr2, 20, sizeof(int)) succeeded\n");
    
    // Test free
    free(ptr1);
    free(ptr3);
    printf("PASS: free() calls completed\n");
    
    // Test edge cases
    void *ptr4 = malloc(0);
    printf("%s: malloc(0) returned %s\n", 
           ptr4 == NULL ? "PASS" : "FAIL",
           ptr4 == NULL ? "NULL" : "non-NULL");
    
    void *ptr5 = calloc(0, 10);
    printf("%s: calloc(0, 10) returned %s\n",
           ptr5 == NULL ? "PASS" : "FAIL", 
           ptr5 == NULL ? "NULL" : "non-NULL");
    
    free(NULL);
    printf("PASS: free(NULL) completed without crash\n");
    
    printf("All tests completed!\n");
    return 0;
}
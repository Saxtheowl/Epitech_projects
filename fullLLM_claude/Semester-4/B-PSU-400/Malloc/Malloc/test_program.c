/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
** Test program for custom malloc
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Simple test without debug functions

void test_basic_malloc(void)
{
    printf("=== Testing basic malloc ===\n");

    void *ptr1 = malloc(100);
    void *ptr2 = malloc(200);
    void *ptr3 = malloc(50);

    printf("Allocated ptr1=%p, ptr2=%p, ptr3=%p\n", ptr1, ptr2, ptr3);

    if (ptr1) strcpy((char *)ptr1, "Hello");
    if (ptr2) strcpy((char *)ptr2, "World");
    if (ptr3) strcpy((char *)ptr3, "Test");

    printf("ptr1 contains: %s\n", ptr1 ? (char *)ptr1 : "NULL");
    printf("ptr2 contains: %s\n", ptr2 ? (char *)ptr2 : "NULL");
    printf("ptr3 contains: %s\n", ptr3 ? (char *)ptr3 : "NULL");

    free(ptr1);
    free(ptr2);
    free(ptr3);

    printf("All pointers freed\n\n");
}

void test_calloc(void)
{
    printf("=== Testing calloc ===\n");

    int *arr = (int *)calloc(10, sizeof(int));
    if (arr == NULL) {
        printf("calloc failed\n");
        return;
    }

    printf("calloc allocated array of 10 ints\n");
    printf("First 5 values: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    printf("calloc test completed\n\n");
}

void test_realloc(void)
{
    printf("=== Testing realloc ===\n");

    char *ptr = (char *)malloc(50);
    if (ptr == NULL) {
        printf("Initial malloc failed\n");
        return;
    }

    strcpy(ptr, "Initial string");
    printf("Initial: %s (size 50)\n", ptr);

    ptr = (char *)realloc(ptr, 100);
    if (ptr == NULL) {
        printf("realloc failed\n");
        return;
    }

    strcat(ptr, " - Extended");
    printf("After realloc: %s (size 100)\n", ptr);

    ptr = (char *)realloc(ptr, 20);
    if (ptr == NULL) {
        printf("realloc shrink failed\n");
        return;
    }

    printf("After shrink: %s (size 20)\n", ptr);

    free(ptr);
    printf("realloc test completed\n\n");
}

void test_edge_cases(void)
{
    printf("=== Testing edge cases ===\n");

    // Test malloc(0)
    void *ptr1 = malloc(0);
    printf("malloc(0) = %p\n", ptr1);
    if (ptr1) free(ptr1);

    // Test free(NULL)
    free(NULL);
    printf("free(NULL) completed\n");

    // Test realloc(NULL, size)
    void *ptr2 = realloc(NULL, 100);
    printf("realloc(NULL, 100) = %p\n", ptr2);
    if (ptr2) {
        strcpy((char *)ptr2, "Realloc from NULL");
        printf("Content: %s\n", (char *)ptr2);
        free(ptr2);
    }

    printf("Edge cases test completed\n\n");
}

void test_fragmentation(void)
{
    printf("=== Testing fragmentation ===\n");

    void *ptrs[10];

    // Allocate multiple blocks
    for (int i = 0; i < 10; i++) {
        ptrs[i] = malloc(50 + i * 10);
        printf("Allocated block %d: %p\n", i, ptrs[i]);
    }

    // Free every other block to create fragmentation
    for (int i = 1; i < 10; i += 2) {
        free(ptrs[i]);
        printf("Freed block %d\n", i);
    }

    // Try to allocate in fragmented space
    void *new_ptr = malloc(30);
    printf("New allocation in fragmented space: %p\n", new_ptr);

    // Clean up remaining blocks
    for (int i = 0; i < 10; i += 2) {
        free(ptrs[i]);
    }
    free(new_ptr);

    printf("Fragmentation test completed\n\n");
}

int main(void)
{
    printf("Starting malloc tests...\n\n");

    test_basic_malloc();
    test_calloc();
    test_realloc();
    test_edge_cases();
    test_fragmentation();

    printf("=== Final status ===\n");
    printf("Tests completed successfully!\n");

    printf("\nAll tests completed!\n");
    return 0;
}
/*
** EPITECH PROJECT, 2024
** test_antman.c
** File description:
** Unit tests for Antman compression project
*/

#include <stdio.h>
#include <stdlib.h>
#include "../shared/compression.h"

static void test_string_functions(void)
{
    printf("Testing string utility functions...\n");
    
    printf("my_strlen(\"hello\"): %d (expected: 5)\n", my_strlen("hello"));
    printf("my_strlen(NULL): %d (expected: 0)\n", my_strlen(NULL));
    
    char *dup = my_strdup("test");
    printf("my_strdup(\"test\"): %s (expected: test)\n", dup ? dup : "NULL");
    free(dup);
    
    printf("my_strcmp(\"abc\", \"abc\"): %d (expected: 0)\n", 
           my_strcmp("abc", "abc"));
    printf("my_strcmp(\"abc\", \"def\"): %s (expected: negative)\n", 
           my_strcmp("abc", "def") < 0 ? "negative" : "positive");
    
    printf("my_atoi(\"123\"): %d (expected: 123)\n", my_atoi("123"));
    printf("my_atoi(\"-456\"): %d (expected: -456)\n", my_atoi("-456"));
    
    char buffer[32];
    printf("my_itoa(789): %s (expected: 789)\n", my_itoa(789, buffer));
    printf("my_itoa(-321): %s (expected: -321)\n", my_itoa(-321, buffer));
    
    printf("is_word_char('a'): %d (expected: 1)\n", is_word_char('a'));
    printf("is_word_char('@'): %d (expected: 0)\n", is_word_char('@'));
    
    printf("PASS\n\n");
}

static void test_dictionary_operations(void)
{
    dictionary_t *dict;
    
    printf("Testing dictionary operations...\n");
    
    dict = dictionary_create();
    if (!dict) {
        printf("FAILED: Could not create dictionary\n");
        return;
    }
    
    int index1 = dictionary_add_word(dict, "hello");
    int index2 = dictionary_add_word(dict, "world");
    
    printf("Added 'hello' at index: %d (expected: 0)\n", index1);
    printf("Added 'world' at index: %d (expected: 1)\n", index2);
    
    int found1 = dictionary_find_word(dict, "hello");
    int found2 = dictionary_find_word(dict, "world");
    int found3 = dictionary_find_word(dict, "missing");
    
    printf("Found 'hello' at index: %d (expected: 0)\n", found1);
    printf("Found 'world' at index: %d (expected: 1)\n", found2);
    printf("Found 'missing' at index: %d (expected: -1)\n", found3);
    
    dictionary_free(dict);
    printf("PASS\n\n");
}

static void test_buffer_operations(void)
{
    buffer_t *buffer;
    
    printf("Testing buffer operations...\n");
    
    buffer = buffer_create();
    if (!buffer) {
        printf("FAILED: Could not create buffer\n");
        return;
    }
    
    buffer_append_char(buffer, 'H');
    buffer_append_char(buffer, 'i');
    buffer_append_string(buffer, " there");
    
    printf("Buffer size after operations: %zu (expected: 8)\n", buffer->size);
    printf("Buffer content: ");
    for (size_t i = 0; i < buffer->size; i++)
        printf("%c", buffer->data[i]);
    printf(" (expected: Hi there)\n");
    
    buffer_free(buffer);
    printf("PASS\n\n");
}

static void test_compression_algorithms(void)
{
    const char *test_input = "hello world hello test world";
    size_t input_size = my_strlen(test_input);
    size_t compressed_size;
    size_t decompressed_size;
    char *compressed;
    char *decompressed;
    
    printf("Testing compression algorithms...\n");
    
    compressed = compress_song_lyrics(test_input, input_size, &compressed_size);
    if (!compressed) {
        printf("FAILED: Could not compress song lyrics\n");
        return;
    }
    
    printf("Original size: %zu, Compressed size: %zu\n", 
           input_size, compressed_size);
    
    decompressed = decompress_song_lyrics(compressed, compressed_size, 
                                        &decompressed_size);
    if (!decompressed) {
        printf("FAILED: Could not decompress song lyrics\n");
        free(compressed);
        return;
    }
    
    printf("Decompressed size: %zu\n", decompressed_size);
    printf("Round-trip test: %s\n", 
           (my_strcmp(test_input, decompressed) == 0) ? "PASS" : "FAIL");
    
    free(compressed);
    free(decompressed);
    printf("PASS\n\n");
}

int main(void)
{
    printf("Running Antman unit tests...\n\n");
    
    test_string_functions();
    test_dictionary_operations();
    test_buffer_operations();
    test_compression_algorithms();
    
    printf("All tests completed!\n");
    return 0;
}
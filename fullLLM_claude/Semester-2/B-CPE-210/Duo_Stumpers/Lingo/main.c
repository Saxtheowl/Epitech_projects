/*
** EPITECH PROJECT, 2024
** Lingo
** File description:
** Lingo word guessing game implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

typedef struct {
    char **words;
    int word_count;
} dictionary_t;

void print_usage(void)
{
    fprintf(stderr, "Usage: ./lingo [word_file]\n");
}

void free_dictionary(dictionary_t *dict)
{
    int i;
    
    if (dict->words) {
        for (i = 0; i < dict->word_count; i++) {
            free(dict->words[i]);
        }
        free(dict->words);
    }
}

int load_dictionary(char *filename, dictionary_t *dict)
{
    FILE *file = fopen(filename, "r");
    char buffer[1024];
    int capacity = 100;
    
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return 84;
    }
    
    dict->words = malloc(sizeof(char*) * capacity);
    if (!dict->words) {
        fclose(file);
        return 84;
    }
    
    dict->word_count = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
        
        if (strlen(buffer) == 0)
            continue;
        
        if (dict->word_count >= capacity) {
            capacity *= 2;
            dict->words = realloc(dict->words, sizeof(char*) * capacity);
            if (!dict->words) {
                fclose(file);
                return 84;
            }
        }
        
        dict->words[dict->word_count] = malloc(strlen(buffer) + 1);
        if (!dict->words[dict->word_count]) {
            fclose(file);
            free_dictionary(dict);
            return 84;
        }
        
        strcpy(dict->words[dict->word_count], buffer);
        dict->word_count++;
    }
    
    fclose(file);
    return 0;
}

char *select_random_word(dictionary_t *dict)
{
    if (dict->word_count == 0)
        return NULL;
    
    int index = rand() % dict->word_count;
    return dict->words[index];
}

void print_initial_hint(char *secret_word)
{
    int i;
    int len = strlen(secret_word);
    
    printf("%c", secret_word[0]);
    for (i = 1; i < len; i++) {
        printf("*");
    }
    printf("\n");
}

int is_letter_in_word(char letter, char *word)
{
    int i;
    
    for (i = 0; word[i]; i++) {
        if (word[i] == letter)
            return 1;
    }
    return 0;
}

void print_feedback(char *guess, char *secret_word)
{
    int i;
    int len = strlen(secret_word);
    
    for (i = 0; i < len; i++) {
        if (guess[i] == secret_word[i]) {
            printf("%c", guess[i]); // Correct position
        } else if (is_letter_in_word(guess[i], secret_word)) {
            printf("?"); // Wrong position
        } else {
            printf("*"); // Not in word
        }
    }
    printf("\n");
}

int play_game(char *secret_word)
{
    char input[1024];
    int word_len = strlen(secret_word);
    int round = 1;
    int max_rounds = word_len;
    
    printf("*: invalid letter\n");
    printf("?: incorrectly placed letter\n");
    printf("Will you find the secret word?\n");
    
    print_initial_hint(secret_word);
    
    while (round <= max_rounds) {
        printf("Round %d\n", round);
        printf(">");
        
        if (!fgets(input, sizeof(input), stdin)) {
            return 0;
        }
        
        // Remove newline
        int input_len = strlen(input);
        if (input_len > 0 && input[input_len - 1] == '\n')
            input[input_len - 1] = '\0';
        
        // Check word length
        if ((int)strlen(input) != word_len) {
            printf("Word too short. Retry.\n");
            continue;
        }
        
        // Check if word is correct
        if (strcmp(input, secret_word) == 0) {
            printf("%s\n", secret_word);
            printf("You won!\n");
            return 1;
        }
        
        // Print feedback
        print_feedback(input, secret_word);
        
        round++;
    }
    
    printf("You lost!\n");
    return 0;
}

int main(int argc, char **argv)
{
    dictionary_t dict;
    char *secret_word;
    
    if (argc != 2) {
        print_usage();
        return 84;
    }
    
    if (load_dictionary(argv[1], &dict) != 0) {
        return 84;
    }
    
    if (dict.word_count == 0) {
        free_dictionary(&dict);
        return 84;
    }
    
    srand(time(NULL));
    secret_word = select_random_word(&dict);
    
    play_game(secret_word);
    
    free_dictionary(&dict);
    return 0;
}
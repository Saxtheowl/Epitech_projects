#include "fastatools.h"

string_builder_t *sb_create(void)
{
    string_builder_t *sb = malloc(sizeof(string_builder_t));
    if (!sb)
        return NULL;
    
    sb->capacity = 1024;
    sb->str = malloc(sb->capacity);
    if (!sb->str) {
        free(sb);
        return NULL;
    }
    
    sb->len = 0;
    sb->str[0] = '\0';
    return sb;
}

void sb_append(string_builder_t *sb, char c)
{
    if (sb->len + 1 >= sb->capacity) {
        sb->capacity *= 2;
        sb->str = realloc(sb->str, sb->capacity);
        if (!sb->str)
            return;
    }
    
    sb->str[sb->len] = c;
    sb->len++;
    sb->str[sb->len] = '\0';
}

void sb_append_str(string_builder_t *sb, const char *str)
{
    int i;
    
    for (i = 0; str[i]; i++) {
        sb_append(sb, str[i]);
    }
}

char *sb_to_string(string_builder_t *sb)
{
    char *result = malloc(sb->len + 1);
    if (!result)
        return NULL;
    
    strcpy(result, sb->str);
    return result;
}

void sb_free(string_builder_t *sb)
{
    if (!sb)
        return;
    
    free(sb->str);
    free(sb);
}

sequence_t *parse_fasta(FILE *input)
{
    char line[4096];
    sequence_t *sequences = NULL;
    sequence_t *current = NULL;
    string_builder_t *sb = NULL;
    
    while (fgets(line, sizeof(line), input)) {
        // Remove newline
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        
        if (line[0] == '>') {
            // New sequence identifier
            if (current && sb) {
                current->data = sb_to_string(sb);
                clean_dna_sequence(current->data);
                sb_free(sb);
            }
            
            // Create new sequence
            sequence_t *new_seq = malloc(sizeof(sequence_t));
            if (!new_seq)
                break;
            
            new_seq->id = malloc(strlen(line) + 1);
            strcpy(new_seq->id, line);
            new_seq->data = NULL;
            new_seq->next = NULL;
            
            if (!sequences) {
                sequences = new_seq;
            } else {
                sequence_t *last = sequences;
                while (last->next)
                    last = last->next;
                last->next = new_seq;
            }
            
            current = new_seq;
            sb = sb_create();
        } else if (current && sb && strlen(line) > 0) {
            // Append sequence data
            sb_append_str(sb, line);
        }
    }
    
    // Handle last sequence
    if (current && sb) {
        current->data = sb_to_string(sb);
        clean_dna_sequence(current->data);
        sb_free(sb);
    }
    
    return sequences;
}

void free_sequences(sequence_t *sequences)
{
    while (sequences) {
        sequence_t *next = sequences->next;
        free(sequences->id);
        free(sequences->data);
        free(sequences);
        sequences = next;
    }
}
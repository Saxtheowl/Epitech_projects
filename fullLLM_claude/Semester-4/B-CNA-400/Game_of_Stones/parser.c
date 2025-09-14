/*
** EPITECH PROJECT, 2024
** Game of Stones
** File description:
** File parsing functions
*/

#include "game_of_stones.h"

char *trim_whitespace(char *str)
{
    char *end;
    
    // Trim leading space
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r')
        str++;
    
    if (*str == 0)  // All spaces?
        return str;
    
    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
        end--;
    
    // Write new null terminator character
    end[1] = '\0';
    
    return str;
}

static int parse_friendship_line(graph_t *graph, char *line)
{
    char *trimmed = trim_whitespace(line);
    
    // Look for pattern: "PersonA is friends with PersonB"
    char *is_friends = strstr(trimmed, " is friends with ");
    if (!is_friends)
        return -1;
    
    // Extract PersonA
    char person_a[MAX_NAME_LEN];
    int name_len = is_friends - trimmed;
    if (name_len >= MAX_NAME_LEN)
        return -1;
    
    strncpy(person_a, trimmed, name_len);
    person_a[name_len] = '\0';
    char *person_a_trimmed = trim_whitespace(person_a);
    
    // Extract PersonB
    char *person_b_start = is_friends + strlen(" is friends with ");
    char person_b[MAX_NAME_LEN];
    strncpy(person_b, person_b_start, MAX_NAME_LEN - 1);
    person_b[MAX_NAME_LEN - 1] = '\0';
    char *person_b_trimmed = trim_whitespace(person_b);
    
    if (strlen(person_a_trimmed) == 0 || strlen(person_b_trimmed) == 0)
        return -1;
    
    // Add persons to graph
    int id_a = add_person(graph, person_a_trimmed);
    int id_b = add_person(graph, person_b_trimmed);
    
    if (id_a == -1 || id_b == -1)
        return -1;
    
    // Add friendship (reciprocal)
    graph->friendship_matrix[id_a][id_b] = 1;
    graph->friendship_matrix[id_b][id_a] = 1;
    
    return 0;
}

static int parse_conspiracy_line(graph_t *graph, char *line)
{
    char *trimmed = trim_whitespace(line);
    
    // Look for pattern: "PersonA is plotting against PersonB"
    char *is_plotting = strstr(trimmed, " is plotting against ");
    if (!is_plotting)
        return -1;
    
    // Extract PersonA
    char person_a[MAX_NAME_LEN];
    int name_len = is_plotting - trimmed;
    if (name_len >= MAX_NAME_LEN)
        return -1;
    
    strncpy(person_a, trimmed, name_len);
    person_a[name_len] = '\0';
    char *person_a_trimmed = trim_whitespace(person_a);
    
    // Extract PersonB
    char *person_b_start = is_plotting + strlen(" is plotting against ");
    char person_b[MAX_NAME_LEN];
    strncpy(person_b, person_b_start, MAX_NAME_LEN - 1);
    person_b[MAX_NAME_LEN - 1] = '\0';
    char *person_b_trimmed = trim_whitespace(person_b);
    
    if (strlen(person_a_trimmed) == 0 || strlen(person_b_trimmed) == 0)
        return -1;
    
    // Add persons to graph (in case they weren't in friendship file)
    int id_a = add_person(graph, person_a_trimmed);
    int id_b = add_person(graph, person_b_trimmed);
    
    if (id_a == -1 || id_b == -1)
        return -1;
    
    // Add conspiracy (not reciprocal)
    graph->conspiracy_matrix[id_a][id_b] = 1;
    
    return 0;
}

int parse_friendship_file(graph_t *graph, char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open friendship file '%s'\n", filename);
        return -1;
    }
    
    char line[MAX_LINE_LEN];
    int line_num = 0;
    
    while (fgets(line, sizeof(line), file)) {
        line_num++;
        
        // Skip empty lines
        char *trimmed = trim_whitespace(line);
        if (strlen(trimmed) == 0)
            continue;
        
        if (parse_friendship_line(graph, line) == -1) {
            fprintf(stderr, "Error: Invalid friendship format at line %d\n", line_num);
            fclose(file);
            return -1;
        }
    }
    
    fclose(file);
    return 0;
}

int parse_conspiracy_file(graph_t *graph, char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open conspiracy file '%s'\n", filename);
        return -1;
    }
    
    char line[MAX_LINE_LEN];
    int line_num = 0;
    
    while (fgets(line, sizeof(line), file)) {
        line_num++;
        
        // Skip empty lines
        char *trimmed = trim_whitespace(line);
        if (strlen(trimmed) == 0)
            continue;
        
        if (parse_conspiracy_line(graph, line) == -1) {
            fprintf(stderr, "Error: Invalid conspiracy format at line %d\n", line_num);
            fclose(file);
            return -1;
        }
    }
    
    fclose(file);
    return 0;
}
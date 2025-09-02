/*
** EPITECH PROJECT, 2025
** Game of Stones
** File description:
** File parsing functions
*/

#include "game_of_stones.h"

static int parse_friendship_line(graph_t *graph, char *line)
{
    char *token;
    char *name1 = NULL, *name2 = NULL;
    char *saveptr;
    char line_copy[MAX_LINE_LEN];
    
    // Remove newline and make a copy
    line[strcspn(line, "\r\n")] = 0;
    strcpy(line_copy, line);
    
    // Parse "Name1 is friends with Name2"
    token = strtok_r(line_copy, " ", &saveptr);
    if (!token)
        return -1;
        
    name1 = strdup(token);
    if (!name1)
        return -1;
    
    // Skip "is friends with"
    token = strtok_r(NULL, " ", &saveptr); // "is"
    if (!token || strcmp(token, "is") != 0) {
        free(name1);
        return -1;
    }
    
    token = strtok_r(NULL, " ", &saveptr); // "friends"  
    if (!token || strcmp(token, "friends") != 0) {
        free(name1);
        return -1;
    }
    
    token = strtok_r(NULL, " ", &saveptr); // "with"
    if (!token || strcmp(token, "with") != 0) {
        free(name1);
        return -1;
    }
    
    // Get second name (rest of the string)
    token = strtok_r(NULL, "", &saveptr);
    if (!token) {
        free(name1);
        return -1;
    }
    
    name2 = strdup(token);
    if (!name2) {
        free(name1);
        return -1;
    }
    
    int idx1 = add_person(graph, name1);
    int idx2 = add_person(graph, name2);
    
    if (idx1 >= 0 && idx2 >= 0) {
        add_friendship(graph, idx1, idx2);
    }
    
    free(name1);
    free(name2);
    
    return (idx1 >= 0 && idx2 >= 0) ? 0 : -1;
}

graph_t *parse_friendship_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return NULL;
    }
    
    graph_t *graph = create_graph();
    if (!graph) {
        fclose(file);
        return NULL;
    }
    
    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        if (parse_friendship_line(graph, line) < 0) {
            continue; // Skip malformed lines
        }
    }
    
    fclose(file);
    calculate_shortest_paths(graph);
    
    return graph;
}

static int parse_conspiracy_line(conspiracies_t *conspiracies, graph_t *graph, char *line)
{
    char *token;
    char *name1 = NULL, *name2 = NULL;
    char *saveptr;
    
    // Remove newline
    line[strcspn(line, "\r\n")] = 0;
    
    // Parse "Name1 is plotting against Name2"
    token = strtok_r(line, " ", &saveptr);
    if (!token)
        return -1;
        
    name1 = strdup(token);
    if (!name1)
        return -1;
    
    // Skip "is plotting against"
    token = strtok_r(NULL, " ", &saveptr); // "is"
    token = strtok_r(NULL, " ", &saveptr); // "plotting"
    token = strtok_r(NULL, " ", &saveptr); // "against"
    
    // Get second name (rest of the string)
    char *remaining = strtok_r(NULL, "", &saveptr);
    if (!remaining) {
        free(name1);
        return -1;
    }
    
    name2 = strdup(remaining);
    if (!name2) {
        free(name1);
        return -1;
    }
    
    int idx1 = find_person(graph, name1);
    int idx2 = find_person(graph, name2);
    
    if (idx1 < 0 || idx2 < 0) {
        fprintf(stderr, "Error: Person in conspiracy not found in friendships\n");
        free(name1);
        free(name2);
        return -1;
    }
    
    if (conspiracies->count >= conspiracies->capacity) {
        conspiracies->capacity *= 2;
        conspiracies->list = realloc(conspiracies->list, 
                                   conspiracies->capacity * sizeof(conspiracy_t));
        if (!conspiracies->list) {
            free(name1);
            free(name2);
            return -1;
        }
    }
    
    conspiracies->list[conspiracies->count].plotter = idx1;
    conspiracies->list[conspiracies->count].target = idx2;
    conspiracies->count++;
    
    free(name1);
    free(name2);
    
    return 0;
}

conspiracies_t *parse_conspiracy_file(const char *filename, graph_t *graph)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return NULL;
    }
    
    conspiracies_t *conspiracies = malloc(sizeof(conspiracies_t));
    if (!conspiracies) {
        fclose(file);
        return NULL;
    }
    
    conspiracies->capacity = 100;
    conspiracies->count = 0;
    conspiracies->list = malloc(sizeof(conspiracy_t) * conspiracies->capacity);
    if (!conspiracies->list) {
        free(conspiracies);
        fclose(file);
        return NULL;
    }
    
    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        if (parse_conspiracy_line(conspiracies, graph, line) < 0) {
            free(conspiracies->list);
            free(conspiracies);
            fclose(file);
            return NULL;
        }
    }
    
    fclose(file);
    return conspiracies;
}
/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Globbing (wildcard expansion) implementation
*/

#include "shell.h"

char **expand_glob(char *pattern)
{
    glob_t globbuf;
    char **result;
    int flags = GLOB_TILDE;
    
    if (glob(pattern, flags, NULL, &globbuf) != 0) {
        // No matches found, return original pattern
        result = malloc(sizeof(char*) * 2);
        if (result) {
            result[0] = my_strdup(pattern);
            result[1] = NULL;
        }
        return result;
    }
    
    // Copy results
    result = malloc(sizeof(char*) * (globbuf.gl_pathc + 1));
    if (!result) {
        globfree(&globbuf);
        return NULL;
    }
    
    for (size_t i = 0; i < globbuf.gl_pathc; i++) {
        result[i] = my_strdup(globbuf.gl_pathv[i]);
        if (!result[i]) {
            free_glob_result(result);
            globfree(&globbuf);
            return NULL;
        }
    }
    
    result[globbuf.gl_pathc] = NULL;
    globfree(&globbuf);
    
    return result;
}

void free_glob_result(char **result)
{
    if (!result) {
        return;
    }
    
    for (int i = 0; result[i]; i++) {
        free(result[i]);
    }
    
    free(result);
}
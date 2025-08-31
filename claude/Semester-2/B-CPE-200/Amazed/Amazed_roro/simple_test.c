#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_chars;
    int line_count = 0;
    
    printf("Starting to read lines...\n");
    
    while ((read_chars = getline(&line, &len, stdin)) != -1) {
        line_count++;
        printf("Line %d (len=%zd): '%s'\n", line_count, read_chars, line);
        
        if (line_count > 10) // Safety break
            break;
    }
    
    printf("Total lines read: %d\n", line_count);
    
    if (line)
        free(line);
        
    return 0;
}
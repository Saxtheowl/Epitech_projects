#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"

char **read_map_from_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    char **world;
    char line[1000];
    int num_lines;
    int i = 0;
    
    if (!file)
        return NULL;
    
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return NULL;
    }
    
    num_lines = atoi(line);
    world = malloc(sizeof(char*) * (num_lines + 1));
    
    while (i < num_lines && fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        world[i] = strdup(line);
        i++;
    }
    
    world[i] = NULL;
    fclose(file);
    return world;
}

void free_world(char **world)
{
    int i = 0;
    if (!world)
        return;
    while (world[i]) {
        free(world[i]);
        i++;
    }
    free(world);
}

void print_world(char **world)
{
    int i = 0;
    while (world[i]) {
        my_putstr(world[i]);
        my_putchar('\n');
        i++;
    }
}

int main(void)
{
    char **world = read_map_from_file("map.txt");
    int result;
    
    if (!world) {
        my_putstr("Error reading map.txt\n");
        return 1;
    }
    
    my_putstr("Original map:\n");
    print_world(world);
    my_putstr("\n");
    
    result = count_island(world);
    
    my_putstr("Map with islands numbered:\n");
    print_world(world);
    my_putstr("\nNumber of islands found: ");
    my_put_nbr(result);
    my_putchar('\n');
    
    free_world(world);
    return 0;
}
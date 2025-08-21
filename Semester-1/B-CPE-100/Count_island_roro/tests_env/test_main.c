/*
** EPITECH PROJECT, 2024
** Count_island
** File description:
** Test main for count_island function
*/

#include "../include/my.h"
#include <fcntl.h>
#include <sys/stat.h>

static int get_file_size(char const *filename)
{
    struct stat st;
    
    if (stat(filename, &st) == -1)
        return -1;
    return st.st_size;
}

static char *read_file(char const *filename)
{
    int fd;
    int size;
    char *buffer;
    int bytes_read;
    
    size = get_file_size(filename);
    if (size == -1)
        return NULL;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return NULL;
    
    buffer = malloc(size + 1);
    if (!buffer) {
        close(fd);
        return NULL;
    }
    
    bytes_read = read(fd, buffer, size);
    close(fd);
    
    if (bytes_read != size) {
        free(buffer);
        return NULL;
    }
    
    buffer[size] = '\0';
    return buffer;
}

static char **create_world_from_file(char const *filename)
{
    char *content;
    char **world;
    int rows = 0;
    int i = 0;
    int j = 0;
    int start = 0;
    
    content = read_file(filename);
    if (!content)
        return NULL;
    
    while (content[i]) {
        if (content[i] == '\n')
            rows++;
        i++;
    }
    if (i > 0 && content[i - 1] != '\n')
        rows++;
    
    world = malloc(sizeof(char *) * (rows + 1));
    if (!world) {
        free(content);
        return NULL;
    }
    
    i = 0;
    j = 0;
    start = 0;
    
    while (j < rows) {
        while (content[i] && content[i] != '\n')
            i++;
        
        world[j] = malloc(i - start + 1);
        if (!world[j]) {
            while (j > 0)
                free(world[--j]);
            free(world);
            free(content);
            return NULL;
        }
        
        for (int k = 0; k < i - start; k++)
            world[j][k] = content[start + k];
        world[j][i - start] = '\0';
        
        if (content[i] == '\n')
            i++;
        start = i;
        j++;
    }
    
    world[rows] = NULL;
    free(content);
    return world;
}

static void free_world(char **world)
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

static void print_world(char **world)
{
    int i = 0;
    
    if (!world)
        return;
    
    while (world[i]) {
        my_putstr(world[i]);
        my_putchar('\n');
        i++;
    }
}

int main(int ac, char **av)
{
    char **world;
    int result;
    
    if (ac != 2) {
        my_putstr("Usage: ./test_main <world_file>\n");
        return 84;
    }
    
    world = create_world_from_file(av[1]);
    if (!world) {
        my_putstr("Error: Could not read file\n");
        return 84;
    }
    
    result = count_island(world);
    
    print_world(world);
    my_putnbr(result);
    my_putchar('\n');
    
    free_world(world);
    return 0;
}
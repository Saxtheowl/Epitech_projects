/*
** EPITECH PROJECT, 2024
** Day12 - my_grep
** File description:
** Implementation of grep command using file descriptors
*/

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#define BUFFER_SIZE 30000

int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        write(1, &str[i], 1);
        i++;
    }
    return (0);
}

int my_strlen(char const *str)
{
    int len = 0;

    while (str[len] != '\0')
        len++;
    return (len);
}

char *my_strstr(char *str, char const *to_find)
{
    int i = 0;
    int j;

    if (*to_find == '\0')
        return (str);

    while (str[i] != '\0') {
        j = 0;
        while (str[i + j] == to_find[j] && to_find[j] != '\0')
            j++;
        if (to_find[j] == '\0')
            return (&str[i]);
        i++;
    }
    return (NULL);
}

void print_line(char *line)
{
    int i = 0;

    while (line[i] != '\0' && line[i] != '\n') {
        write(1, &line[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

char **split_lines(char *content, int *line_count)
{
    char **lines;
    int count = 1;
    int i = 0;
    int line_idx = 0;
    int start = 0;

    while (content[i] != '\0') {
        if (content[i] == '\n')
            count++;
        i++;
    }

    lines = malloc(sizeof(char *) * (count + 1));
    if (lines == NULL)
        return (NULL);

    i = 0;
    start = 0;
    while (content[i] != '\0') {
        if (content[i] == '\n' || content[i + 1] == '\0') {
            lines[line_idx] = malloc(sizeof(char) * (i - start + 2));
            if (lines[line_idx] == NULL)
                return (NULL);
            for (int j = 0; j < i - start + (content[i + 1] == '\0' ? 1 : 0); j++) {
                lines[line_idx][j] = content[start + j];
            }
            lines[line_idx][i - start + (content[i + 1] == '\0' ? 1 : 0)] = '\0';
            line_idx++;
            start = i + 1;
        }
        i++;
    }
    lines[line_idx] = NULL;
    *line_count = count;
    return (lines);
}

int grep_file(char const *pattern, char const *filename)
{
    int fd;
    char *buffer;
    char **lines;
    int bytes_read;
    int line_count;
    int found = 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        my_putstr("grep: ");
        my_putstr(filename);
        my_putstr(": No such file or directory\n");
        return (2);
    }

    buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL)
        return (2);

    bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    close(fd);

    if (bytes_read == -1) {
        free(buffer);
        return (2);
    }

    buffer[bytes_read] = '\0';
    lines = split_lines(buffer, &line_count);
    
    if (lines == NULL) {
        free(buffer);
        return (2);
    }

    for (int i = 0; lines[i] != NULL; i++) {
        if (my_strstr(lines[i], pattern) != NULL) {
            print_line(lines[i]);
            found = 1;
        }
        free(lines[i]);
    }

    free(lines);
    free(buffer);
    return (found ? 0 : 1);
}

int main(int argc, char **argv)
{
    int i;
    int exit_status = 0;
    int found_any = 0;

    if (argc < 3) {
        my_putstr("Usage: grep pattern file...\n");
        return (2);
    }

    for (i = 2; i < argc; i++) {
        int result = grep_file(argv[1], argv[i]);
        if (result == 0)
            found_any = 1;
        else if (result == 2)
            exit_status = 2;
    }

    if (exit_status == 2)
        return (2);
    return (found_any ? 0 : 1);
}
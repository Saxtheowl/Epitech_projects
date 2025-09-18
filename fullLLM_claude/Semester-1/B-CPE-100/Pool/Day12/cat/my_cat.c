/*
** EPITECH PROJECT, 2024
** Day12 - my_cat
** File description:
** Implementation of cat command using file descriptors
*/

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

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

int display_file_content(int fd)
{
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(1, buffer, bytes_read) == -1) {
            return (84);
        }
    }
    
    if (bytes_read == -1) {
        return (84);
    }
    
    return (0);
}

int cat_file(char const *filename)
{
    int fd;
    int result;

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        my_putstr("cat: ");
        my_putstr(filename);
        my_putstr(": No such file or directory\n");
        return (84);
    }

    result = display_file_content(fd);
    close(fd);
    return (result);
}

int cat_stdin(void)
{
    return (display_file_content(0));
}

int main(int argc, char **argv)
{
    int i;
    int exit_status = 0;

    if (argc == 1) {
        return (cat_stdin());
    }

    for (i = 1; i < argc; i++) {
        if (cat_file(argv[i]) == 84) {
            exit_status = 84;
        }
    }

    return (exit_status);
}
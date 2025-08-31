/*
** Debug program to test parsing
*/

#include "include/amazed.h"

int main(void)
{
    maze_t *maze = create_maze();
    char *line = NULL;
    size_t len = 0;
    ssize_t read_chars;
    int is_start = 0, is_end = 0;
    
    while ((read_chars = getline(&line, &len, stdin)) != -1) {
        if (read_chars > 0 && line[read_chars - 1] == '\n')
            line[read_chars - 1] = '\0';
            
        printf("Read line: '%s'\n", line);
        
        if (line[0] == '#' && line[1] == '#') {
            printf("Command detected: %s\n", line);
            if (my_strcmp(line, "##start") == 0) {
                is_start = 1;
                printf("Set is_start = 1\n");
            } else if (my_strcmp(line, "##end") == 0) {
                is_end = 1;
                printf("Set is_end = 1\n");
            }
        } else if (line[0] >= '0' && line[0] <= '9' && maze->robot_count == 0) {
            printf("Parsing robot count\n");
            parse_number_of_robots(maze, line);
        } else if (strchr(line, '-') == NULL && line[0] != '#') {
            printf("Parsing room with is_start=%d, is_end=%d\n", is_start, is_end);
            parse_room(maze, line, &is_start, &is_end);
            printf("After parsing room: start_room=%d, end_room=%d\n", maze->start_room, maze->end_room);
        }
    }
    
    printf("Final: start_room=%d, end_room=%d\n", maze->start_room, maze->end_room);
    cleanup_maze(maze);
    return 0;
}
/*
** EPITECH PROJECT, 2025
** RobotFactory
** File description:
** Argument parsing functions
*/

#include "asm.h"

static char *get_output_filename(char *input_file)
{
    char *output;
    char *dot_pos;
    int len;
    
    if (!input_file)
        return NULL;
    
    dot_pos = strrchr(input_file, '.');
    if (!dot_pos || strcmp(dot_pos, ".s") != 0)
        return NULL;
    
    len = dot_pos - input_file;
    output = malloc(len + 5);
    if (!output)
        return NULL;
    
    strncpy(output, input_file, len);
    output[len] = '\0';
    strcat(output, ".cor");
    
    return output;
}

int parse_arguments(int ac, char **av, asm_t *assembler)
{
    if (ac != 2)
        return 84;
    
    if (!av[1] || strlen(av[1]) < 3)
        return 84;
    
    if (strcmp(av[1] + strlen(av[1]) - 2, ".s") != 0)
        return 84;
    
    assembler->input_file = av[1];
    assembler->output_file = get_output_filename(av[1]);
    
    if (!assembler->output_file)
        return 84;
    
    return 0;
}

void print_usage(void)
{
    printf("USAGE\n");
    printf("    ./asm file_name[.s]\n");
    printf("DESCRIPTION\n");
    printf("    file_name file in assembly language to be converted into file_name.cor, an executable in the Virtual Machine.\n");
}

int parse_file(asm_t *assembler)
{
    FILE *file;
    char line[1024];
    int line_num = 0;
    int header_parsed = 0;
    
    file = fopen(assembler->input_file, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", assembler->input_file);
        return 84;
    }
    
    while (fgets(line, sizeof(line), file)) {
        line_num++;
        
        if (is_empty_line(line) || is_comment_line(line))
            continue;
        
        if (!header_parsed) {
            if (strncmp(line, ".name", 5) == 0) {
                if (extract_name(line, assembler->header.prog_name) != 0) {
                    fprintf(stderr, "Error: Invalid name format at line %d\n", line_num);
                    fclose(file);
                    return 84;
                }
                continue;
            }
            
            if (strncmp(line, ".comment", 8) == 0) {
                if (extract_comment(line, assembler->header.comment) != 0) {
                    fprintf(stderr, "Error: Invalid comment format at line %d\n", line_num);
                    fclose(file);
                    return 84;
                }
                header_parsed = 1;
                continue;
            }
        }
        
        if (is_label_line(line)) {
            if (parse_label(line, assembler) != 0) {
                fprintf(stderr, "Error: Invalid label at line %d\n", line_num);
                fclose(file);
                return 84;
            }
        } else {
            char *trimmed = trim_whitespace(line);
            if (trimmed && trimmed[0] != '\0') {
                if (parse_instruction_line(line, assembler) != 0) {
                    fprintf(stderr, "Error: Invalid instruction at line %d\n", line_num);
                    fclose(file);
                    return 84;
                }
            }
        }
    }
    
    if (assembler->header.prog_name[0] == '\0' || 
        assembler->header.comment[0] == '\0') {
        fprintf(stderr, "Error: Missing name or comment\n");
        fclose(file);
        return 84;
    }
    
    fclose(file);
    return 0;
}
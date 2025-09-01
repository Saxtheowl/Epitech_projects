/*
** EPITECH PROJECT, 2025
** RobotFactory
** File description:
** Header parsing functions
*/

#include "asm.h"
#include "op.h"

static int extract_string(char *line, char *start_delimiter, char *output, int max_len)
{
    char *start, *end;
    int len;
    
    start = strstr(line, start_delimiter);
    if (!start)
        return 84;
    
    start = strchr(start, '"');
    if (!start)
        return 84;
    start++;
    
    end = strrchr(start, '"');
    if (!end || end == start)
        return 84;
    
    len = end - start;
    if (len > max_len)
        return 84;
    
    strncpy(output, start, len);
    output[len] = '\0';
    
    return 0;
}

int extract_name(char *line, char *name)
{
    return extract_string(line, ".name", name, PROG_NAME_LENGTH);
}

int extract_comment(char *line, char *comment)
{
    return extract_string(line, ".comment", comment, COMMENT_LENGTH);
}

void add_label(asm_t *assembler, char *name, int position)
{
    label_t *new_label, *current;
    
    new_label = malloc(sizeof(label_t));
    if (!new_label)
        return;
    
    new_label->name = strdup(name);
    new_label->position = position;
    new_label->next = NULL;
    
    if (!assembler->labels) {
        assembler->labels = new_label;
        return;
    }
    
    current = assembler->labels;
    while (current->next)
        current = current->next;
    
    current->next = new_label;
}

label_t *find_label(asm_t *assembler, char *name)
{
    label_t *current = assembler->labels;
    
    while (current) {
        if (strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }
    
    return NULL;
}

int resolve_label_value(asm_t *assembler, char *label_name, int current_pos)
{
    label_t *label = find_label(assembler, label_name);
    
    if (!label)
        return 0;
    
    return label->position - current_pos;
}

int parse_label(char *line, asm_t *assembler)
{
    char *colon_pos, *label_name, *instruction_part;
    int len;
    
    line = trim_whitespace(line);
    colon_pos = strchr(line, LABEL_CHAR);
    if (!colon_pos)
        return 84;
    
    len = colon_pos - line;
    label_name = malloc(len + 1);
    if (!label_name)
        return 84;
    
    strncpy(label_name, line, len);
    label_name[len] = '\0';
    label_name = trim_whitespace(label_name);
    
    add_label(assembler, label_name, assembler->current_pos);
    
    instruction_part = trim_whitespace(colon_pos + 1);
    if (instruction_part && instruction_part[0] != '\0') {
        if (parse_instruction_line(instruction_part, assembler) != 0) {
            free(label_name);
            return 84;
        }
    }
    
    free(label_name);
    return 0;
}
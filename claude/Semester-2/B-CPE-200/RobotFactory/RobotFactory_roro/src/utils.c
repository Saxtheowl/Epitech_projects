/*
** EPITECH PROJECT, 2025
** RobotFactory
** File description:
** Utility functions for assembler
*/

#include "asm.h"
#include "op.h"

char *trim_whitespace(char *str)
{
    char *end;
    
    if (!str)
        return NULL;
    
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r')
        str++;
    
    if (*str == 0)
        return str;
    
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
        end--;
    
    *(end + 1) = '\0';
    
    return str;
}

int is_label_line(char *line)
{
    char *colon_pos;
    char *trimmed;
    
    if (!line)
        return 0;
    
    trimmed = trim_whitespace(line);
    colon_pos = strchr(trimmed, LABEL_CHAR);
    
    if (!colon_pos)
        return 0;
    
    // Check if colon is part of a parameter like %:label, not a label definition
    if (colon_pos > trimmed && *(colon_pos - 1) == '%')
        return 0;
    
    return 1;
}

int is_comment_line(char *line)
{
    char *trimmed;
    
    if (!line)
        return 0;
    
    trimmed = trim_whitespace(line);
    return (trimmed[0] == COMMENT_CHAR);
}

int is_empty_line(char *line)
{
    char *trimmed;
    
    if (!line)
        return 1;
    
    trimmed = trim_whitespace(line);
    return (trimmed[0] == '\0');
}

void write_big_endian_int(FILE *file, unsigned int value)
{
    unsigned char bytes[4];
    
    bytes[0] = (value >> 24) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >> 8) & 0xFF;
    bytes[3] = value & 0xFF;
    
    fwrite(bytes, 1, 4, file);
}

void write_big_endian_short(FILE *file, unsigned short value)
{
    unsigned char bytes[2];
    
    bytes[0] = (value >> 8) & 0xFF;
    bytes[1] = value & 0xFF;
    
    fwrite(bytes, 1, 2, file);
}

void free_assembler(asm_t *assembler)
{
    instruction_t *inst, *next_inst;
    label_t *label, *next_label;
    int i;
    
    if (!assembler)
        return;
    
    if (assembler->output_file)
        free(assembler->output_file);
    
    inst = assembler->instructions;
    while (inst) {
        next_inst = inst->next;
        for (i = 0; i < inst->arg_count; i++) {
            if (inst->args[i])
                free(inst->args[i]);
        }
        if (inst->args)
            free(inst->args);
        free(inst);
        inst = next_inst;
    }
    
    label = assembler->labels;
    while (label) {
        next_label = label->next;
        if (label->name)
            free(label->name);
        free(label);
        label = next_label;
    }
}
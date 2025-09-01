/*
** EPITECH PROJECT, 2025
** RobotFactory
** File description:
** Assembler main functions
*/

#include "asm.h"

static instruction_t *create_instruction(op_t *op)
{
    instruction_t *inst = malloc(sizeof(instruction_t));
    
    if (!inst)
        return NULL;
    
    inst->op = op;
    inst->args = NULL;
    inst->arg_count = 0;
    inst->position = 0;
    inst->coding_byte = 0;
    inst->next = NULL;
    
    return inst;
}

static char **parse_instruction_arguments(char *args_str, int *arg_count)
{
    char **args = malloc(sizeof(char*) * MAX_ARGS_NUMBER);
    char *token, *str_copy;
    int count = 0;
    
    if (!args || !args_str)
        return NULL;
    
    str_copy = strdup(args_str);
    if (!str_copy) {
        free(args);
        return NULL;
    }
    
    token = strtok(str_copy, ",");
    while (token && count < MAX_ARGS_NUMBER) {
        args[count] = strdup(trim_whitespace(token));
        count++;
        token = strtok(NULL, ",");
    }
    
    *arg_count = count;
    free(str_copy);
    return args;
}

int parse_instruction_line(char *line, asm_t *assembler)
{
    char *mnemonic, *args_str;
    op_t *op;
    instruction_t *inst, *current;
    char *space_pos;
    
    line = trim_whitespace(line);
    if (!line || line[0] == '\0')
        return 0;
    
    space_pos = strchr(line, ' ');
    if (space_pos) {
        *space_pos = '\0';
        mnemonic = trim_whitespace(line);
        args_str = trim_whitespace(space_pos + 1);
    } else {
        mnemonic = trim_whitespace(line);
        args_str = NULL;
    }
    
    op = get_operation(mnemonic);
    if (!op) {
        fprintf(stderr, "Error: Unknown instruction %s\n", mnemonic);
        return 84;
    }
    
    inst = create_instruction(op);
    if (!inst)
        return 84;
    
    inst->position = assembler->current_pos;
    
    if (args_str && strlen(args_str) > 0) {
        inst->args = parse_instruction_arguments(args_str, &inst->arg_count);
        if (!inst->args) {
            free(inst);
            return 84;
        }
    }
    
    if (inst->arg_count != op->nbr_args) {
        fprintf(stderr, "Error: Wrong number of arguments for %s\n", mnemonic);
        free(inst);
        return 84;
    }
    
    inst->coding_byte = generate_coding_byte(inst);
    assembler->current_pos += calculate_instruction_size(inst);
    
    if (!assembler->instructions) {
        assembler->instructions = inst;
    } else {
        current = assembler->instructions;
        while (current->next)
            current = current->next;
        current->next = inst;
    }
    
    return 0;
}

int generate_bytecode(asm_t *assembler)
{
    FILE *output;
    instruction_t *current;
    int total_size = 0;
    
    current = assembler->instructions;
    while (current) {
        total_size += calculate_instruction_size(current);
        current = current->next;
    }
    
    assembler->header.prog_size = total_size;
    
    output = fopen(assembler->output_file, "wb");
    if (!output) {
        fprintf(stderr, "Error: Cannot create output file %s\n", assembler->output_file);
        return 84;
    }
    
    // Write header structure
    write_big_endian_int(output, assembler->header.magic);
    
    // Write program name (128 bytes, null-terminated)
    fwrite(assembler->header.prog_name, 1, strlen(assembler->header.prog_name), output);
    for (int i = strlen(assembler->header.prog_name); i < PROG_NAME_LENGTH; i++) {
        fputc('\0', output);
    }
    
    // Write 4 null bytes
    fwrite("\0\0\0\0", 1, 4, output);
    
    // Write program size
    write_big_endian_int(output, assembler->header.prog_size);
    
    // Write comment (2048 bytes, null-terminated)  
    fwrite(assembler->header.comment, 1, strlen(assembler->header.comment), output);
    for (int i = strlen(assembler->header.comment); i < COMMENT_LENGTH; i++) {
        fputc('\0', output);
    }
    
    // Write 4 null bytes
    fwrite("\0\0\0\0", 1, 4, output);
    
    current = assembler->instructions;
    while (current) {
        unsigned char opcode = current->op->code;
        fwrite(&opcode, 1, 1, output);
        
        if (current->op->coding_byte) {
            fwrite(&current->coding_byte, 1, 1, output);
        }
        
        for (int i = 0; i < current->arg_count; i++) {
            unsigned char param_bytes[4] = {0};
            int param_size = encode_parameter(current->args[i], current->op, i, 
                                            param_bytes, assembler);
            if (param_size > 0) {
                fwrite(param_bytes, 1, param_size, output);
            }
        }
        
        current = current->next;
    }
    
    fclose(output);
    return 0;
}
/*
** EPITECH PROJECT, 2025
** RobotFactory
** File description:
** Bytecode generation functions
*/

#include "asm.h"

static int get_param_size(char *param, op_t *op, int param_index)
{
    (void)param_index;
    
    if (is_valid_register(param))
        return 1;
    
    if (is_direct_param(param)) {
        if (op->dir_size)
            return 2;
        else
            return 4;
    }
    
    if (is_indirect_param(param))
        return 2;
    
    return 0;
}

int calculate_instruction_size(instruction_t *inst)
{
    int size = 1;
    int i;
    
    if (inst->op->coding_byte)
        size += 1;
    
    for (i = 0; i < inst->arg_count; i++) {
        size += get_param_size(inst->args[i], inst->op, i);
    }
    
    return size;
}

unsigned char generate_coding_byte(instruction_t *inst)
{
    unsigned char coding_byte = 0;
    int i;
    
    if (!inst->op->coding_byte)
        return 0;
    
    for (i = 0; i < inst->arg_count; i++) {
        unsigned char param_type = 0;
        
        if (is_valid_register(inst->args[i])) {
            param_type = REG_CODE;
        } else if (is_direct_param(inst->args[i])) {
            param_type = DIR_CODE;
        } else if (is_indirect_param(inst->args[i])) {
            param_type = IND_CODE;
        }
        
        coding_byte |= (param_type << (6 - (i * 2)));
    }
    
    return coding_byte;
}

static int encode_register(char *param, unsigned char *buffer)
{
    int reg_num = atoi(param + 1);
    
    buffer[0] = (unsigned char)reg_num;
    return 1;
}

static int encode_direct(char *param, op_t *op, unsigned char *buffer, asm_t *assembler, int current_pos)
{
    char *value_str = param + 1;
    int value;
    
    if (value_str[0] == ':') {
        value = resolve_label_value(assembler, value_str + 1, current_pos);
    } else {
        value = atoi(value_str);
    }
    
    if (op->dir_size) {
        buffer[0] = (value >> 8) & 0xFF;
        buffer[1] = value & 0xFF;
        return 2;
    } else {
        buffer[0] = (value >> 24) & 0xFF;
        buffer[1] = (value >> 16) & 0xFF;
        buffer[2] = (value >> 8) & 0xFF;
        buffer[3] = value & 0xFF;
        return 4;
    }
}

static int encode_indirect(char *param, unsigned char *buffer, asm_t *assembler, int current_pos)
{
    int value;
    
    if (param[0] == ':') {
        value = resolve_label_value(assembler, param + 1, current_pos);
    } else {
        value = atoi(param);
    }
    
    buffer[0] = (value >> 8) & 0xFF;
    buffer[1] = value & 0xFF;
    return 2;
}

int encode_parameter(char *param, op_t *op, int param_index, 
                    unsigned char *buffer, asm_t *assembler)
{
    int current_pos = 0;
    instruction_t *current = assembler->instructions;
    
    while (current && current->args != NULL && current->args[param_index] != param) {
        current_pos += calculate_instruction_size(current);
        current = current->next;
    }
    
    if (is_valid_register(param)) {
        return encode_register(param, buffer);
    }
    
    if (is_direct_param(param)) {
        return encode_direct(param, op, buffer, assembler, current_pos);
    }
    
    if (is_indirect_param(param)) {
        return encode_indirect(param, buffer, assembler, current_pos);
    }
    
    return 0;
}
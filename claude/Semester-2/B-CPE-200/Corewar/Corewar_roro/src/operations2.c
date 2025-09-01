/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Implementation of remaining Corewar instructions
*/

#include "corewar.h"

// 0x09 - zjmp
void op_zjmp(vm_t *vm, process_t *process)
{
    int address = read_memory(vm, process->pc + 1, IND_SIZE);
    
    if (process->carry) {
        process->pc = (process->pc + (address % IDX_MOD)) % MEM_SIZE;
    } else {
        process->pc = (process->pc + 1 + IND_SIZE) % MEM_SIZE;
    }
}

// 0x0a - ldi
void op_ldi(vm_t *vm, process_t *process)
{
    int coding_byte = read_memory(vm, process->pc + 1, 1);
    int offset = 2;
    
    int param1_type = (coding_byte >> 6) & 0x3;
    int param2_type = (coding_byte >> 4) & 0x3;
    int param3_type = (coding_byte >> 2) & 0x3;
    
    if (param3_type != 1) {
        process->pc = (process->pc + 1) % MEM_SIZE;
        return;
    }
    
    int val1 = get_argument_value(vm, process, param1_type == 1 ? T_REG : 
                                  param1_type == 2 ? T_DIR : T_IND, offset);
    offset += (param1_type == 1 ? 1 : param1_type == 2 ? IND_SIZE : IND_SIZE);
    
    int val2 = get_argument_value(vm, process, param2_type == 1 ? T_REG : 
                                  param2_type == 2 ? T_DIR : T_IND, offset);
    offset += (param2_type == 1 ? 1 : IND_SIZE);
    
    int reg_num = read_memory(vm, process->pc + offset, 1);
    
    if (reg_num >= 1 && reg_num <= REG_NUMBER) {
        int sum = val1 + val2;
        int value = read_memory(vm, (process->pc + sum) % IDX_MOD, REG_SIZE);
        process->registers[reg_num - 1] = value;
        process->carry = (value == 0) ? 1 : 0;
    }
    
    process->pc = (process->pc + offset + 1) % MEM_SIZE;
}

// 0x0b - sti
void op_sti(vm_t *vm, process_t *process)
{
    int coding_byte = read_memory(vm, process->pc + 1, 1);
    int offset = 2;
    
    int param1_type = (coding_byte >> 6) & 0x3;
    int param2_type = (coding_byte >> 4) & 0x3;
    int param3_type = (coding_byte >> 2) & 0x3;
    
    if (param1_type != 1) {
        process->pc = (process->pc + 1) % MEM_SIZE;
        return;
    }
    
    int reg_num = read_memory(vm, process->pc + offset, 1);
    offset += 1;
    
    if (reg_num < 1 || reg_num > REG_NUMBER) {
        process->pc = (process->pc + 1) % MEM_SIZE;
        return;
    }
    
    int reg_value = process->registers[reg_num - 1];
    
    int val2 = get_argument_value(vm, process, param2_type == 1 ? T_REG : 
                                  param2_type == 2 ? T_DIR : T_IND, offset);
    offset += (param2_type == 1 ? 1 : param2_type == 2 ? IND_SIZE : IND_SIZE);
    
    int val3 = get_argument_value(vm, process, param3_type == 1 ? T_REG : 
                                  param3_type == 2 ? T_DIR : T_IND, offset);
    offset += (param3_type == 1 ? 1 : IND_SIZE);
    
    int address = (process->pc + ((val2 + val3) % IDX_MOD)) % MEM_SIZE;
    write_memory(vm, address, reg_value, REG_SIZE);
    
    process->pc = (process->pc + offset) % MEM_SIZE;
}

// 0x0c - fork
void op_fork(vm_t *vm, process_t *process)
{
    int address = read_memory(vm, process->pc + 1, IND_SIZE);
    int new_pc = (process->pc + (address % IDX_MOD)) % MEM_SIZE;
    
    process_t *new_process = create_process(process->champion_id, new_pc);
    if (new_process) {
        // Copy registers
        for (int i = 0; i < REG_NUMBER; i++) {
            new_process->registers[i] = process->registers[i];
        }
        new_process->carry = process->carry;
        add_process(vm, new_process);
    }
    
    process->pc = (process->pc + 1 + IND_SIZE) % MEM_SIZE;
}

// 0x0d - lld (long load)
void op_lld(vm_t *vm, process_t *process)
{
    int coding_byte = read_memory(vm, process->pc + 1, 1);
    int offset = 2;
    
    int param1_type = (coding_byte >> 6) & 0x3;
    int param2_type = (coding_byte >> 4) & 0x3;
    
    if (param2_type != 1) {
        process->pc = (process->pc + 1) % MEM_SIZE;
        return;
    }
    
    int value = 0;
    if (param1_type == 2) { // T_DIR
        value = read_memory(vm, process->pc + offset, DIR_SIZE);
        offset += DIR_SIZE;
    } else if (param1_type == 3) { // T_IND
        int address = read_memory(vm, process->pc + offset, IND_SIZE);
        value = read_memory(vm, process->pc + address, REG_SIZE); // No modulo
        offset += IND_SIZE;
    }
    
    int reg_num = read_memory(vm, process->pc + offset, 1);
    if (reg_num >= 1 && reg_num <= REG_NUMBER) {
        process->registers[reg_num - 1] = value;
        process->carry = (value == 0) ? 1 : 0;
    }
    
    process->pc = (process->pc + 1 + 1 + 
                   (param1_type == 2 ? DIR_SIZE : IND_SIZE) + 1) % MEM_SIZE;
}

// 0x0e - lldi (long load index)
void op_lldi(vm_t *vm, process_t *process)
{
    int coding_byte = read_memory(vm, process->pc + 1, 1);
    int offset = 2;
    
    int param1_type = (coding_byte >> 6) & 0x3;
    int param2_type = (coding_byte >> 4) & 0x3;
    int param3_type = (coding_byte >> 2) & 0x3;
    
    if (param3_type != 1) {
        process->pc = (process->pc + 1) % MEM_SIZE;
        return;
    }
    
    int val1 = get_argument_value(vm, process, param1_type == 1 ? T_REG : 
                                  param1_type == 2 ? T_DIR : T_IND, offset);
    offset += (param1_type == 1 ? 1 : param1_type == 2 ? IND_SIZE : IND_SIZE);
    
    int val2 = get_argument_value(vm, process, param2_type == 1 ? T_REG : 
                                  param2_type == 2 ? T_DIR : T_IND, offset);
    offset += (param2_type == 1 ? 1 : IND_SIZE);
    
    int reg_num = read_memory(vm, process->pc + offset, 1);
    
    if (reg_num >= 1 && reg_num <= REG_NUMBER) {
        int sum = val1 + val2;
        int value = read_memory(vm, process->pc + sum, REG_SIZE); // No modulo
        process->registers[reg_num - 1] = value;
        process->carry = (value == 0) ? 1 : 0;
    }
    
    process->pc = (process->pc + offset + 1) % MEM_SIZE;
}

// 0x0f - lfork (long fork)
void op_lfork(vm_t *vm, process_t *process)
{
    int address = read_memory(vm, process->pc + 1, IND_SIZE);
    int new_pc = (process->pc + address) % MEM_SIZE; // No modulo
    
    process_t *new_process = create_process(process->champion_id, new_pc);
    if (new_process) {
        // Copy registers
        for (int i = 0; i < REG_NUMBER; i++) {
            new_process->registers[i] = process->registers[i];
        }
        new_process->carry = process->carry;
        add_process(vm, new_process);
    }
    
    process->pc = (process->pc + 1 + IND_SIZE) % MEM_SIZE;
}

// 0x10 - aff
void op_aff(vm_t *vm, process_t *process)
{
    int coding_byte = read_memory(vm, process->pc + 1, 1);
    
    int param1_type = (coding_byte >> 6) & 0x3;
    
    if (param1_type != 1) {
        process->pc = (process->pc + 1) % MEM_SIZE;
        return;
    }
    
    int reg_num = read_memory(vm, process->pc + 2, 1);
    
    if (reg_num >= 1 && reg_num <= REG_NUMBER) {
        char c = (char)(process->registers[reg_num - 1] % 256);
        write(1, &c, 1);
    }
    
    process->pc = (process->pc + 1 + 1 + 1) % MEM_SIZE;
}
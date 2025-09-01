/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Implementation of all Corewar instructions
*/

#include "corewar.h"

// 0x01 - live
void op_live(vm_t *vm, process_t *process)
{
    int champion_id = read_memory(vm, process->pc + 1, DIR_SIZE);
    
    process->last_live = vm->cycle;
    vm->last_live_champion = champion_id;
    
    printf("The player %d(%s) is alive.\n", champion_id, "champion");
    
    process->pc = (process->pc + 1 + DIR_SIZE) % MEM_SIZE;
}

// 0x02 - ld
void op_ld(vm_t *vm, process_t *process)
{
    int coding_byte = read_memory(vm, process->pc + 1, 1);
    int offset = 2;
    
    int param1_type = (coding_byte >> 6) & 0x3;
    int param2_type = (coding_byte >> 4) & 0x3;
    
    if (param1_type == 0 || param2_type != 1) {
        process->pc = (process->pc + 1) % MEM_SIZE;
        return;
    }
    
    int value = 0;
    if (param1_type == 2) { // T_DIR
        value = read_memory(vm, process->pc + offset, DIR_SIZE);
        offset += DIR_SIZE;
    } else if (param1_type == 3) { // T_IND
        int address = read_memory(vm, process->pc + offset, IND_SIZE);
        value = read_memory(vm, (process->pc + address) % IDX_MOD, REG_SIZE);
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

// 0x03 - st
void op_st(vm_t *vm, process_t *process)
{
    int coding_byte = read_memory(vm, process->pc + 1, 1);
    int offset = 2;
    
    int param1_type = (coding_byte >> 6) & 0x3;
    int param2_type = (coding_byte >> 4) & 0x3;
    
    if (param1_type != 1 || (param2_type != 1 && param2_type != 3)) {
        process->pc = (process->pc + 1) % MEM_SIZE;
        return;
    }
    
    int reg_num = read_memory(vm, process->pc + offset, 1);
    offset += 1;
    
    if (reg_num < 1 || reg_num > REG_NUMBER) {
        process->pc = (process->pc + 1) % MEM_SIZE;
        return;
    }
    
    int value = process->registers[reg_num - 1];
    
    if (param2_type == 1) { // Register
        int target_reg = read_memory(vm, process->pc + offset, 1);
        if (target_reg >= 1 && target_reg <= REG_NUMBER) {
            process->registers[target_reg - 1] = value;
        }
        offset += 1;
    } else if (param2_type == 3) { // Indirect
        int address = read_memory(vm, process->pc + offset, IND_SIZE);
        write_memory(vm, (process->pc + address) % IDX_MOD, value, REG_SIZE);
        offset += IND_SIZE;
    }
    
    process->pc = (process->pc + 1 + 1 + 1 + 
                   (param2_type == 1 ? 1 : IND_SIZE)) % MEM_SIZE;
}

// 0x04 - add
void op_add(vm_t *vm, process_t *process)
{
    int coding_byte = read_memory(vm, process->pc + 1, 1);
    (void)coding_byte;
    
    int reg1 = read_memory(vm, process->pc + 2, 1);
    int reg2 = read_memory(vm, process->pc + 3, 1);
    int reg3 = read_memory(vm, process->pc + 4, 1);
    
    if (reg1 >= 1 && reg1 <= REG_NUMBER && 
        reg2 >= 1 && reg2 <= REG_NUMBER && 
        reg3 >= 1 && reg3 <= REG_NUMBER) {
        
        int result = process->registers[reg1 - 1] + process->registers[reg2 - 1];
        process->registers[reg3 - 1] = result;
        process->carry = (result == 0) ? 1 : 0;
    }
    
    process->pc = (process->pc + 5) % MEM_SIZE;
}

// 0x05 - sub
void op_sub(vm_t *vm, process_t *process)
{
    int coding_byte = read_memory(vm, process->pc + 1, 1);
    (void)coding_byte;
    
    int reg1 = read_memory(vm, process->pc + 2, 1);
    int reg2 = read_memory(vm, process->pc + 3, 1);
    int reg3 = read_memory(vm, process->pc + 4, 1);
    
    if (reg1 >= 1 && reg1 <= REG_NUMBER && 
        reg2 >= 1 && reg2 <= REG_NUMBER && 
        reg3 >= 1 && reg3 <= REG_NUMBER) {
        
        int result = process->registers[reg1 - 1] - process->registers[reg2 - 1];
        process->registers[reg3 - 1] = result;
        process->carry = (result == 0) ? 1 : 0;
    }
    
    process->pc = (process->pc + 5) % MEM_SIZE;
}

// 0x06 - and
void op_and(vm_t *vm, process_t *process)
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
    offset += (param1_type == 1 ? 1 : param1_type == 2 ? DIR_SIZE : IND_SIZE);
    
    int val2 = get_argument_value(vm, process, param2_type == 1 ? T_REG : 
                                  param2_type == 2 ? T_DIR : T_IND, offset);
    offset += (param2_type == 1 ? 1 : param2_type == 2 ? DIR_SIZE : IND_SIZE);
    
    int reg_num = read_memory(vm, process->pc + offset, 1);
    
    if (reg_num >= 1 && reg_num <= REG_NUMBER) {
        int result = val1 & val2;
        process->registers[reg_num - 1] = result;
        process->carry = (result == 0) ? 1 : 0;
    }
    
    process->pc = (process->pc + offset + 1) % MEM_SIZE;
}

// 0x07 - or
void op_or(vm_t *vm, process_t *process)
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
    offset += (param1_type == 1 ? 1 : param1_type == 2 ? DIR_SIZE : IND_SIZE);
    
    int val2 = get_argument_value(vm, process, param2_type == 1 ? T_REG : 
                                  param2_type == 2 ? T_DIR : T_IND, offset);
    offset += (param2_type == 1 ? 1 : param2_type == 2 ? DIR_SIZE : IND_SIZE);
    
    int reg_num = read_memory(vm, process->pc + offset, 1);
    
    if (reg_num >= 1 && reg_num <= REG_NUMBER) {
        int result = val1 | val2;
        process->registers[reg_num - 1] = result;
        process->carry = (result == 0) ? 1 : 0;
    }
    
    process->pc = (process->pc + offset + 1) % MEM_SIZE;
}

// 0x08 - xor
void op_xor(vm_t *vm, process_t *process)
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
    offset += (param1_type == 1 ? 1 : param1_type == 2 ? DIR_SIZE : IND_SIZE);
    
    int val2 = get_argument_value(vm, process, param2_type == 1 ? T_REG : 
                                  param2_type == 2 ? T_DIR : T_IND, offset);
    offset += (param2_type == 1 ? 1 : param2_type == 2 ? DIR_SIZE : IND_SIZE);
    
    int reg_num = read_memory(vm, process->pc + offset, 1);
    
    if (reg_num >= 1 && reg_num <= REG_NUMBER) {
        int result = val1 ^ val2;
        process->registers[reg_num - 1] = result;
        process->carry = (result == 0) ? 1 : 0;
    }
    
    process->pc = (process->pc + offset + 1) % MEM_SIZE;
}
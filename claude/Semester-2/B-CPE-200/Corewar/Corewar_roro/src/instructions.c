/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Instruction execution and memory management
*/

#include "corewar.h"

static void (*instruction_table[])(vm_t *, process_t *) = {
    op_live,    // 0x01
    op_ld,      // 0x02
    op_st,      // 0x03
    op_add,     // 0x04
    op_sub,     // 0x05
    op_and,     // 0x06
    op_or,      // 0x07
    op_xor,     // 0x08
    op_zjmp,    // 0x09
    op_ldi,     // 0x0a
    op_sti,     // 0x0b
    op_fork,    // 0x0c
    op_lld,     // 0x0d
    op_lldi,    // 0x0e
    op_lfork,   // 0x0f
    op_aff      // 0x10
};

int read_memory(vm_t *vm, int address, int size)
{
    int value = 0;
    
    address = ((address % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
    
    for (int i = 0; i < size; i++) {
        value = (value << 8) | (unsigned char)vm->memory[(address + i) % MEM_SIZE];
    }
    
    return value;
}

void write_memory(vm_t *vm, int address, int value, int size)
{
    address = ((address % MEM_SIZE) + MEM_SIZE) % MEM_SIZE;
    
    for (int i = size - 1; i >= 0; i--) {
        vm->memory[(address + i) % MEM_SIZE] = (value >> (i * 8)) & 0xFF;
    }
}

static int get_param_size(int param_type, int instruction)
{
    if (param_type == T_REG)
        return 1;
    if (param_type == T_IND)
        return IND_SIZE;
    if (param_type == T_DIR) {
        // For certain instructions, direct parameters are 2 bytes instead of 4
        if (instruction == 9 || instruction == 10 || instruction == 11 || 
            instruction == 12 || instruction == 14 || instruction == 15)
            return IND_SIZE;
        return DIR_SIZE;
    }
    return 0;
}


int get_argument_value(vm_t *vm, process_t *process, int arg_type, int offset)
{
    int param_value = 0;
    
    if (arg_type == T_REG) {
        int reg_num = read_memory(vm, process->pc + offset, 1);
        if (reg_num < 1 || reg_num > REG_NUMBER)
            return 0;
        return process->registers[reg_num - 1];
    } else if (arg_type == T_DIR) {
        return read_memory(vm, process->pc + offset, get_param_size(T_DIR, 0));
    } else if (arg_type == T_IND) {
        int address = read_memory(vm, process->pc + offset, IND_SIZE);
        return read_memory(vm, process->pc + (address % IDX_MOD), REG_SIZE);
    }
    
    return param_value;
}

void execute_instruction(vm_t *vm, process_t *process)
{
    int opcode = vm->memory[process->pc] & 0xFF;
    
    if (opcode < 1 || opcode > 16) {
        process->pc = (process->pc + 1) % MEM_SIZE;
        return;
    }
    
    // Get instruction info from op_tab
    op_t *op = NULL;
    for (int i = 0; op_tab[i].mnemonique; i++) {
        if (op_tab[i].code == opcode) {
            op = &op_tab[i];
            break;
        }
    }
    
    if (!op) {
        process->pc = (process->pc + 1) % MEM_SIZE;
        return;
    }
    
    // Set cycles to wait
    process->cycles_to_wait = op->nbr_cycles - 1;
    
    // Execute instruction
    if (opcode >= 1 && opcode <= 16) {
        instruction_table[opcode - 1](vm, process);
    } else {
        process->pc = (process->pc + 1) % MEM_SIZE;
    }
}
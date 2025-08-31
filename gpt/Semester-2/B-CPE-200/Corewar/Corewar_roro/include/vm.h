/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** Minimal VM structures and API
*/

#ifndef VM_H
#define VM_H

#include "corewar.h"
#include "op.h"

typedef struct process_s {
    int pc;
    int regs[REG_NUMBER];
    int alive;
} process_t;

typedef struct vm_s {
    unsigned char arena[MEM_SIZE];
    process_t *procs;
    int proc_count;
} vm_t;

int vm_init(vm_t *vm, champion_t *champs, int count);
void vm_run(vm_t *vm, int cycles);

#endif /* VM_H */

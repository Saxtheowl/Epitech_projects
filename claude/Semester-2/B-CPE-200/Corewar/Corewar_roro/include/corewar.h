/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Header file for Corewar virtual machine
*/

#ifndef COREWAR_H
#define COREWAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "op.h"

#define MAX_CHAMPIONS 4
#define SUCCESS 0
#define ERROR 84

typedef struct process_s {
    int id;
    int champion_id;
    int registers[REG_NUMBER];
    int pc;
    int carry;
    int cycles_to_wait;
    int last_live;
    struct process_s *next;
} process_t;

typedef struct champion_s {
    int id;
    char name[PROG_NAME_LENGTH + 1];
    char comment[COMMENT_LENGTH + 1];
    int prog_size;
    int load_address;
    int last_live;
    char *code;
} champion_t;

typedef struct vm_s {
    char memory[MEM_SIZE];
    process_t *processes;
    champion_t *champions[MAX_CHAMPIONS];
    int nb_champions;
    int cycle;
    int cycle_to_die;
    int checks;
    int dump_cycle;
    int processes_alive;
    int last_live_champion;
} vm_t;

// Core functions
int load_champion(vm_t *vm, char *filename, int champion_id, int load_address);
int init_vm(vm_t *vm);
int run_vm(vm_t *vm);
void dump_memory(vm_t *vm);

// Process functions
process_t *create_process(int champion_id, int pc);
void add_process(vm_t *vm, process_t *process);
void remove_process(vm_t *vm, process_t *process);

// Instruction functions
void execute_instruction(vm_t *vm, process_t *process);
int get_argument_value(vm_t *vm, process_t *process, int arg_type, int offset);
void write_memory(vm_t *vm, int address, int value, int size);
int read_memory(vm_t *vm, int address, int size);

// Instructions
void op_live(vm_t *vm, process_t *process);
void op_ld(vm_t *vm, process_t *process);
void op_st(vm_t *vm, process_t *process);
void op_add(vm_t *vm, process_t *process);
void op_sub(vm_t *vm, process_t *process);
void op_and(vm_t *vm, process_t *process);
void op_or(vm_t *vm, process_t *process);
void op_xor(vm_t *vm, process_t *process);
void op_zjmp(vm_t *vm, process_t *process);
void op_ldi(vm_t *vm, process_t *process);
void op_sti(vm_t *vm, process_t *process);
void op_fork(vm_t *vm, process_t *process);
void op_lld(vm_t *vm, process_t *process);
void op_lldi(vm_t *vm, process_t *process);
void op_lfork(vm_t *vm, process_t *process);
void op_aff(vm_t *vm, process_t *process);

// Utility functions
int parse_arguments(int argc, char **argv, vm_t *vm);
void usage(void);
void free_vm(vm_t *vm);

#endif
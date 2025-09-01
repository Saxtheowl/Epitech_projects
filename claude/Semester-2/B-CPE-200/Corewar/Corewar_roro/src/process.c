/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Process management functions
*/

#include "corewar.h"

process_t *create_process(int champion_id, int pc)
{
    process_t *process = malloc(sizeof(process_t));
    
    if (!process)
        return NULL;
    
    process->champion_id = champion_id;
    process->pc = pc % MEM_SIZE;
    process->carry = 0;
    process->cycles_to_wait = 0;
    process->last_live = 0;
    process->next = NULL;
    
    for (int i = 0; i < REG_NUMBER; i++)
        process->registers[i] = 0;
    
    return process;
}

void add_process(vm_t *vm, process_t *process)
{
    process->next = vm->processes;
    vm->processes = process;
    vm->processes_alive++;
}

void remove_process(vm_t *vm, process_t *process)
{
    process_t *current = vm->processes;
    process_t *prev = NULL;
    
    while (current) {
        if (current == process) {
            if (prev)
                prev->next = current->next;
            else
                vm->processes = current->next;
            free(current);
            vm->processes_alive--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void free_vm(vm_t *vm)
{
    // Free all processes
    while (vm->processes) {
        process_t *to_free = vm->processes;
        vm->processes = vm->processes->next;
        free(to_free);
    }
    
    // Free all champions
    for (int i = 0; i < vm->nb_champions; i++) {
        if (vm->champions[i]) {
            free(vm->champions[i]->code);
            free(vm->champions[i]);
        }
    }
}
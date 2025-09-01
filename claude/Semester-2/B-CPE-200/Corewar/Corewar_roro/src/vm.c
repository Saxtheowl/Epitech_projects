/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Virtual machine core functions
*/

#include "corewar.h"

int init_vm(vm_t *vm)
{
    vm->cycle = 0;
    vm->cycle_to_die = CYCLE_TO_DIE;
    vm->checks = 0;
    vm->processes_alive = 0;
    vm->last_live_champion = 0;
    vm->processes = NULL;
    
    memset(vm->memory, 0, MEM_SIZE);
    
    // Load champions into memory and create initial processes
    for (int i = 0; i < vm->nb_champions; i++) {
        champion_t *champ = vm->champions[i];
        
        // Copy champion code to memory
        for (int j = 0; j < champ->prog_size; j++) {
            vm->memory[(champ->load_address + j) % MEM_SIZE] = champ->code[j];
        }
        
        // Create initial process for champion
        process_t *process = create_process(champ->id, champ->load_address);
        if (!process)
            return ERROR;
        
        process->registers[0] = champ->id; // r1 = champion id
        add_process(vm, process);
    }
    
    return SUCCESS;
}

static void check_live_processes(vm_t *vm)
{
    process_t *current = vm->processes;
    process_t *prev = NULL;
    int live_count = 0;
    
    while (current) {
        if (vm->cycle - current->last_live > vm->cycle_to_die) {
            process_t *to_remove = current;
            if (prev)
                prev->next = current->next;
            else
                vm->processes = current->next;
            current = current->next;
            free(to_remove);
            vm->processes_alive--;
        } else {
            live_count++;
            prev = current;
            current = current->next;
        }
    }
    
    vm->checks++;
    if (vm->checks >= NBR_LIVE) {
        vm->cycle_to_die -= CYCLE_DELTA;
        vm->checks = 0;
    }
}

void dump_memory(vm_t *vm)
{
    for (int i = 0; i < MEM_SIZE; i++) {
        if (i % 32 == 0 && i != 0)
            printf("\n");
        printf("%02X", (unsigned char)vm->memory[i]);
    }
    printf("\n");
}

int run_vm(vm_t *vm)
{
    int check_cycle = vm->cycle_to_die;
    
    printf("Introducing contestants...\n");
    for (int i = 0; i < vm->nb_champions; i++) {
        printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
               vm->champions[i]->id, vm->champions[i]->prog_size,
               vm->champions[i]->name, vm->champions[i]->comment);
    }
    
    while (vm->processes_alive > 0 || vm->processes) {
        vm->cycle++;
        
        // Execute all processes
        process_t *current = vm->processes;
        while (current) {
            if (current->cycles_to_wait <= 0) {
                execute_instruction(vm, current);
            } else {
                current->cycles_to_wait--;
            }
            current = current->next;
        }
        
        // Check for dump
        if (vm->dump_cycle > 0 && vm->cycle >= vm->dump_cycle) {
            dump_memory(vm);
            return SUCCESS;
        }
        
        // Check live processes
        if (vm->cycle >= check_cycle) {
            check_live_processes(vm);
            check_cycle += vm->cycle_to_die;
        }
        
        if (!vm->processes)
            break;
    }
    
    if (vm->last_live_champion > 0) {
        for (int i = 0; i < vm->nb_champions; i++) {
            if (vm->champions[i]->id == vm->last_live_champion) {
                printf("The player %d(%s)has won.\n",
                       vm->champions[i]->id, vm->champions[i]->name);
                break;
            }
        }
    }
    
    return SUCCESS;
}
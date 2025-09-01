/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Command line parser for Corewar
*/

#include "corewar.h"

void usage(void)
{
    printf("USAGE\n");
    printf("\t./corewar [-dump nbr_cycle] [[-n prog_number] ");
    printf("[-a load_address] prog_name] ...\n\n");
    printf("DESCRIPTION\n");
    printf("\t-dump nbr_cycle\tdumps the memory after the nbr_cycle ");
    printf("execution (if the round isn't\n");
    printf("\t\t\talready over) with the following format: ");
    printf("32 bytes/line in hexadecimal\n");
    printf("\t-n prog_number\tsets the next program's number. ");
    printf("By default, the first free number in the\n");
    printf("\t\t\tparameter order\n");
    printf("\t-a load_address\tsets the next program's loading address. ");
    printf("When no address is specified,\n");
    printf("\t\t\toptimize the addresses so that the processes ");
    printf("are as far away from each other as\n");
    printf("\t\t\tpossible. The addresses are MEM_SIZE modulo.\n");
}

static int set_champion_id(vm_t *vm, int id)
{
    if (id < 1 || id > MAX_CHAMPIONS)
        return ERROR;
    for (int i = 0; i < vm->nb_champions; i++) {
        if (vm->champions[i] && vm->champions[i]->id == id)
            return ERROR;
    }
    return SUCCESS;
}

static int get_next_free_id(vm_t *vm)
{
    for (int id = 1; id <= MAX_CHAMPIONS; id++) {
        int found = 0;
        for (int i = 0; i < vm->nb_champions; i++) {
            if (vm->champions[i] && vm->champions[i]->id == id) {
                found = 1;
                break;
            }
        }
        if (!found)
            return id;
    }
    return ERROR;
}

int parse_arguments(int argc, char **argv, vm_t *vm)
{
    int next_id = 1;
    int next_address = -1;

    if (argc < 2) {
        usage();
        return ERROR;
    }
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-dump") == 0 && i + 1 < argc) {
            vm->dump_cycle = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            next_id = atoi(argv[++i]);
            if (set_champion_id(vm, next_id) == ERROR)
                return ERROR;
        } else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
            next_address = atoi(argv[++i]) % MEM_SIZE;
        } else if (argv[i][0] != '-') {
            if (vm->nb_champions >= MAX_CHAMPIONS)
                return ERROR;
            if (next_id == -1)
                next_id = get_next_free_id(vm);
            if (load_champion(vm, argv[i], next_id, next_address) == ERROR)
                return ERROR;
            next_id = -1;
            next_address = -1;
        }
    }
    
    if (vm->nb_champions == 0)
        return ERROR;
    return SUCCESS;
}
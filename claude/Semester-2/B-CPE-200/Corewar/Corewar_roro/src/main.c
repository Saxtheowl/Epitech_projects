/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Main function for Corewar virtual machine
*/

#include "corewar.h"

int main(int argc, char **argv)
{
    vm_t vm = {0};

    if (parse_arguments(argc, argv, &vm) == ERROR)
        return ERROR;
    if (init_vm(&vm) == ERROR)
        return ERROR;
    if (run_vm(&vm) == ERROR) {
        free_vm(&vm);
        return ERROR;
    }
    free_vm(&vm);
    return SUCCESS;
}
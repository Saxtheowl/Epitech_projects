/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** VM and placement tests
*/

#include <criterion/criterion.h>
#include <string.h>
#include <stdlib.h>
#include "corewar.h"
#include "vm.h"

Test(corewar, place_two_champions)
{
    unsigned char arena[MEM_SIZE];
    champion_t champs[2];
    unsigned char code1[2] = {0xAA, 0xBB};
    unsigned char code2[2] = {0xCC, 0xDD};

    memset(arena, 0, sizeof(arena));
    memset(&champs, 0, sizeof(champs));
    champs[0].hdr.prog_size = 2; champs[0].code = code1;
    champs[1].hdr.prog_size = 2; champs[1].code = code2;
    cr_assert(place_champions(arena, MEM_SIZE, champs, 2));
    cr_assert_geq(champs[0].load_addr, 0);
    cr_assert_geq(champs[1].load_addr, 0);
    cr_assert_eq(arena[champs[0].load_addr], 0xAA);
    cr_assert_eq(arena[champs[1].load_addr], 0xCC);
}

Test(corewar, vm_init_sets_pc)
{
    vm_t vm;
    champion_t champ;
    unsigned char code[2] = {0x10, 0x01};
    champ.hdr.prog_size = 2; champ.code = code; champ.load_addr = 123;
    cr_assert(vm_init(&vm, &champ, 1));
    cr_assert_eq(vm.proc_count, 1);
    cr_assert_eq(vm.procs[0].pc, 123);
    free(vm.procs);
}

Test(corewar, exec_ld_dir_to_reg)
{
    vm_t vm;
    process_t *pr;
    memset(&vm, 0, sizeof(vm));
    /* Program: ld %0x0000002A, r2 -> opcode 0x02, coding 0x90, 00 00 00 2A, 0x02 */
    vm.arena[0] = 0x02; vm.arena[1] = 0x90; vm.arena[2] = 0x00; vm.arena[3] = 0x00; vm.arena[4] = 0x00; vm.arena[5] = 0x2A; vm.arena[6] = 0x02;
    vm.proc_count = 1;
    vm.procs = calloc(1, sizeof(process_t));
    pr = &vm.procs[0]; pr->pc = 0; memset(pr->regs, 0, sizeof(pr->regs));
    /* single step via vm_run(1) */
    vm_run(&vm, 1);
    cr_assert_eq(pr->regs[1], 42);
    free(vm.procs);
}

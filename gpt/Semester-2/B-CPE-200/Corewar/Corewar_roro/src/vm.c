/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** Minimal VM loop with very small subset (live, aff)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vm.h"

static int mod_mem(int v)
{
    while (v < 0)
        v += MEM_SIZE;
    if (v >= MEM_SIZE)
        v %= MEM_SIZE;
    return v;
}

static int read_be32_from(const unsigned char *mem, int pos)
{
    int a = mem[mod_mem(pos)] & 0xFF;
    int b = mem[mod_mem(pos + 1)] & 0xFF;
    int c = mem[mod_mem(pos + 2)] & 0xFF;
    int d = mem[mod_mem(pos + 3)] & 0xFF;
    return (a << 24) | (b << 16) | (c << 8) | d;
}

int vm_init(vm_t *vm, champion_t *champs, int count)
{
    int i;

    memset(vm, 0, sizeof(*vm));
    /* place code already done by place_champions; just copy it in */
    for (i = 0; i < count; ++i) {
        memcpy(vm->arena + champs[i].load_addr,
               champs[i].code, (size_t)champs[i].hdr.prog_size);
    }
    vm->procs = calloc((size_t)count, sizeof(process_t));
    if (!vm->procs)
        return 0;
    vm->proc_count = count;
    for (i = 0; i < count; ++i) {
        vm->procs[i].pc = champs[i].load_addr;
        memset(vm->procs[i].regs, 0, sizeof(vm->procs[i].regs));
        vm->procs[i].regs[0] = i + 1; /* r1 id */
        vm->procs[i].alive = 1;
    }
    return 1;
}

static void exec_live(process_t *p)
{
    (void)p; /* In this minimal VM, just acknowledge */
}

static void exec_aff(vm_t *vm, process_t *p)
{
    int reg;
    int pc = p->pc;
    /* Minimalistic parse: opcode(0x10) then reg id (1..16). */
    (void)vm;
    reg = vm->arena[mod_mem(pc + 1)];
    if (reg >= 1 && reg <= REG_NUMBER) {
        int v = p->regs[reg - 1] & 0xFF;
        putchar((char)v);
        fflush(stdout);
    }
    p->pc = mod_mem(pc + 2);
}

static void exec_ld(vm_t *vm, process_t *p)
{
    /* opcode 0x02, coding byte: first arg DIR (10), second REG (01) */
    unsigned char code = vm->arena[mod_mem(p->pc + 1)];
    int pc = p->pc;
    int dir; int reg;
    if (((code & 0xC0) == 0x80) && ((code & 0x30) == 0x10)) {
        dir = read_be32_from(vm->arena, pc + 2);
        reg = vm->arena[mod_mem(pc + 6)];
        if (reg >= 1 && reg <= REG_NUMBER)
            p->regs[reg - 1] = dir;
        p->pc = mod_mem(pc + 7);
    } else {
        /* unsupported form: skip opcode + coding */
        p->pc = mod_mem(pc + 2);
    }
}

static void step_process(vm_t *vm, process_t *p)
{
    unsigned char op = vm->arena[mod_mem(p->pc)];
    if (op == 0x01) { /* live */
        exec_live(p);
        p->pc = mod_mem(p->pc + 5); /* skip direct arg (4 bytes) */
        return;
    }
    if (op == 0x02) { /* ld */
        exec_ld(vm, p);
        return;
    }
    if (op == 0x10) { /* aff (simplified) */
        exec_aff(vm, p);
        return;
    }
    /* Unknown: advance */
    p->pc = mod_mem(p->pc + 1);
}

void vm_run(vm_t *vm, int cycles)
{
    int c;
    int i;
    for (c = 0; c < cycles; ++c) {
        for (i = 0; i < vm->proc_count; ++i)
            step_process(vm, &vm->procs[i]);
    }
}

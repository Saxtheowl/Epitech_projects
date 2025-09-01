#
# EPITECH PROJECT, 2025
# MiniLibC
# File description:
# memset implementation
#

.section .text
.global memset

memset:
    push %rdi            # save original pointer
    mov %rsi, %rax       # move value to rax
    mov %rdx, %rcx       # move count to rcx
    rep stosb            # repeat store byte
    pop %rax             # restore original pointer to return
    ret
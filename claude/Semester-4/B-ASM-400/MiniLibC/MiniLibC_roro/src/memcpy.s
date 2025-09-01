# EPITECH PROJECT, 2025
# MiniLibC - memcpy implementation

.section .text
.global memcpy

memcpy:
    push %rdi
    mov %rdi, %rax
    mov %rdx, %rcx
    rep movsb
    pop %rax
    ret
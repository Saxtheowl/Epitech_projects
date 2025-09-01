# EPITECH PROJECT, 2025
# MiniLibC - memmove implementation

.section .text
.global memmove

memmove:
    push %rdi
    mov %rdi, %rax
    cmp %rsi, %rdi
    jbe .forward
    add %rdx, %rdi
    add %rdx, %rsi
    dec %rdi
    dec %rsi
    std
    mov %rdx, %rcx
    rep movsb
    cld
    jmp .done
.forward:
    mov %rdx, %rcx
    rep movsb
.done:
    pop %rax
    ret
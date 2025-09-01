# EPITECH PROJECT, 2025
# MiniLibC - strpbrk implementation

.section .text
.global strpbrk

strpbrk:
    push %rbx
    push %rcx
.outer_loop:
    movb (%rdi), %al
    test %al, %al
    jz .not_found
    mov %rsi, %rcx
.inner_loop:
    movb (%rcx), %bl
    test %bl, %bl
    jz .next_char
    cmp %bl, %al
    je .found
    inc %rcx
    jmp .inner_loop
.next_char:
    inc %rdi
    jmp .outer_loop
.found:
    mov %rdi, %rax
    jmp .done
.not_found:
    xor %rax, %rax
.done:
    pop %rcx
    pop %rbx
    ret

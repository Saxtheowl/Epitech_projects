# EPITECH PROJECT, 2025
# MiniLibC - strcspn implementation

.section .text
.global strcspn

strcspn:
    push %rbx
    push %rcx
    xor %rax, %rax
.outer_loop:
    movb (%rdi, %rax), %dl
    test %dl, %dl
    jz .done
    mov %rsi, %rcx
.inner_loop:
    movb (%rcx), %bl
    test %bl, %bl
    jz .next_char
    cmp %bl, %dl
    je .done
    inc %rcx
    jmp .inner_loop
.next_char:
    inc %rax
    jmp .outer_loop
.done:
    pop %rcx
    pop %rbx
    ret

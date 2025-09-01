# EPITECH PROJECT, 2025
# MiniLibC - strstr implementation

.section .text
.global strstr

strstr:
    push %rbx
    push %rcx
    push %rdx
    movb (%rsi), %al
    test %al, %al
    jz .return_haystack
.outer_loop:
    movb (%rdi), %bl
    test %bl, %bl
    jz .not_found
    cmp %al, %bl
    jne .next_char
    mov %rdi, %rcx
    mov %rsi, %rdx
.inner_loop:
    movb (%rcx), %bl
    movb (%rdx), %al
    test %al, %al
    jz .found
    test %bl, %bl
    jz .not_found
    cmp %al, %bl
    jne .next_char
    inc %rcx
    inc %rdx
    jmp .inner_loop
.next_char:
    inc %rdi
    movb (%rsi), %al
    jmp .outer_loop
.found:
    mov %rdi, %rax
    jmp .done
.return_haystack:
    mov %rdi, %rax
    jmp .done
.not_found:
    xor %rax, %rax
.done:
    pop %rdx
    pop %rcx
    pop %rbx
    ret

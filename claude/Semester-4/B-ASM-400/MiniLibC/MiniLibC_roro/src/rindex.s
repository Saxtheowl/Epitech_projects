# EPITECH PROJECT, 2025
# MiniLibC - rindex implementation

.section .text
.global rindex

rindex:
    xor %rax, %rax
    mov %sil, %dl
.loop:
    movb (%rdi), %cl
    test %cl, %cl
    jz .done
    cmp %dl, %cl
    jne .next
    mov %rdi, %rax
.next:
    inc %rdi
    jmp .loop
.done:
    ret

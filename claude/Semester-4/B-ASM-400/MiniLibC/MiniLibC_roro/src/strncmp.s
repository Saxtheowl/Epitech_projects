# EPITECH PROJECT, 2025
# MiniLibC - strncmp implementation

.section .text
.global strncmp

strncmp:
    test %rdx, %rdx
    jz .equal
.loop:
    movb (%rdi), %al
    movb (%rsi), %bl
    test %al, %al
    jz .check_end
    cmp %bl, %al
    jne .not_equal
    inc %rdi
    inc %rsi
    dec %rdx
    jnz .loop
.equal:
    xor %rax, %rax
    ret
.check_end:
    test %bl, %bl
    jz .equal
.not_equal:
    movzbl %al, %eax
    movzbl %bl, %ebx
    sub %ebx, %eax
    ret
# EPITECH PROJECT, 2025
# MiniLibC - strcmp implementation

.section .text
.global strcmp

strcmp:
.loop:
    movb (%rdi), %al
    movb (%rsi), %bl
    test %al, %al
    jz .check_end
    cmp %bl, %al
    jne .not_equal
    inc %rdi
    inc %rsi
    jmp .loop
.check_end:
    test %bl, %bl
    jz .equal
.not_equal:
    movzbl %al, %eax
    movzbl %bl, %ebx
    sub %ebx, %eax
    ret
.equal:
    xor %rax, %rax
    ret
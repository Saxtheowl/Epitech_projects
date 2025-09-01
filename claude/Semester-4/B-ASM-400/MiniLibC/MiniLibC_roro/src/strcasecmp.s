# EPITECH PROJECT, 2025
# MiniLibC - strcasecmp implementation

.section .text
.global strcasecmp

strcasecmp:
.loop:
    movb (%rdi), %al
    movb (%rsi), %bl
    cmpb $65, %al
    jb .check_bl
    cmpb $90, %al
    ja .check_bl
    add $32, %al
.check_bl:
    cmpb $65, %bl
    jb .compare
    cmpb $90, %bl
    ja .compare
    add $32, %bl
.compare:
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

#
# EPITECH PROJECT, 2025
# MiniLibC
# File description:
# strlen implementation
#

.section .text
.global strlen

strlen:
    xor %rax, %rax        # clear counter
.loop:
    cmpb $0, (%rdi, %rax)  # check if current byte is null
    je .done              # if null, we're done
    inc %rax              # increment counter
    jmp .loop             # continue loop
.done:
    ret                   # return length in rax
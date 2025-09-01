#
# EPITECH PROJECT, 2025
# MiniLibC
# File description:
# strchr implementation
#

.section .text
.global strchr

strchr:
    mov %sil, %al         # move character to search into al
.loop:
    movb (%rdi), %bl      # load current byte
    cmp %al, %bl          # compare with search character
    je .found             # if equal, found it
    test %bl, %bl         # check if end of string
    jz .not_found         # if null, not found
    inc %rdi              # move to next character
    jmp .loop             # continue loop
.found:
    mov %rdi, %rax        # return pointer to found character
    ret
.not_found:
    xor %rax, %rax        # return NULL
    ret
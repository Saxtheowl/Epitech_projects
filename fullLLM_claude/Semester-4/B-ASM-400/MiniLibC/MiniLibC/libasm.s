.section .text

# strlen implementation
.globl strlen
strlen:
    pushq %rbp
    movq %rsp, %rbp
    xorq %rax, %rax
.strlen_loop:
    cmpb $0, (%rdi,%rax)
    je .strlen_end
    incq %rax
    jmp .strlen_loop
.strlen_end:
    popq %rbp
    ret

# strchr implementation
.globl strchr
strchr:
    pushq %rbp
    movq %rsp, %rbp
.strchr_loop:
    movb (%rdi), %al
    cmpb %sil, %al
    je .strchr_found
    testb %al, %al
    jz .strchr_not_found
    incq %rdi
    jmp .strchr_loop
.strchr_found:
    movq %rdi, %rax
    jmp .strchr_end
.strchr_not_found:
    xorq %rax, %rax
.strchr_end:
    popq %rbp
    ret

# memset implementation
.globl memset
memset:
    pushq %rbp
    movq %rsp, %rbp
    movq %rdi, %rax
    testq %rdx, %rdx
    jz .memset_end
.memset_loop:
    movb %sil, (%rdi)
    incq %rdi
    decq %rdx
    jnz .memset_loop
.memset_end:
    popq %rbp
    ret

# memcpy implementation
.globl memcpy
memcpy:
    pushq %rbp
    movq %rsp, %rbp
    movq %rdi, %rax
    testq %rdx, %rdx
    jz .memcpy_end
.memcpy_loop:
    movb (%rsi), %cl
    movb %cl, (%rdi)
    incq %rdi
    incq %rsi
    decq %rdx
    jnz .memcpy_loop
.memcpy_end:
    popq %rbp
    ret

# strcmp implementation
.globl strcmp
strcmp:
    pushq %rbp
    movq %rsp, %rbp
.strcmp_loop:
    movb (%rdi), %al
    movb (%rsi), %bl
    cmpb %bl, %al
    jne .strcmp_diff
    testb %al, %al
    jz .strcmp_equal
    incq %rdi
    incq %rsi
    jmp .strcmp_loop
.strcmp_diff:
    movzbq %al, %rax
    movzbq %bl, %rbx
    subq %rbx, %rax
    jmp .strcmp_end
.strcmp_equal:
    xorq %rax, %rax
.strcmp_end:
    popq %rbp
    ret

# memmove implementation
.globl memmove
memmove:
    pushq %rbp
    movq %rsp, %rbp
    movq %rdi, %rax
    testq %rdx, %rdx
    jz .memmove_end
    cmpq %rdi, %rsi
    jb .memmove_forward
    # Copy backwards
    addq %rdx, %rdi
    addq %rdx, %rsi
    decq %rdi
    decq %rsi
.memmove_backward:
    movb (%rsi), %cl
    movb %cl, (%rdi)
    decq %rdi
    decq %rsi
    decq %rdx
    jnz .memmove_backward
    jmp .memmove_end
.memmove_forward:
    movb (%rsi), %cl
    movb %cl, (%rdi)
    incq %rdi
    incq %rsi
    decq %rdx
    jnz .memmove_forward
.memmove_end:
    popq %rbp
    ret

# strncmp implementation
.globl strncmp
strncmp:
    pushq %rbp
    movq %rsp, %rbp
    testq %rdx, %rdx
    jz .strncmp_equal
.strncmp_loop:
    movb (%rdi), %al
    movb (%rsi), %bl
    cmpb %bl, %al
    jne .strncmp_diff
    testb %al, %al
    jz .strncmp_equal
    incq %rdi
    incq %rsi
    decq %rdx
    jnz .strncmp_loop
.strncmp_equal:
    xorq %rax, %rax
    jmp .strncmp_end
.strncmp_diff:
    movzbq %al, %rax
    movzbq %bl, %rbx
    subq %rbx, %rax
.strncmp_end:
    popq %rbp
    ret

# strcasecmp implementation
.globl strcasecmp
strcasecmp:
    pushq %rbp
    movq %rsp, %rbp
.strcasecmp_loop:
    movb (%rdi), %al
    movb (%rsi), %bl
    # Convert al to lowercase
    cmpb $'A', %al
    jb .strcasecmp_check_bl
    cmpb $'Z', %al
    ja .strcasecmp_check_bl
    addb $32, %al
.strcasecmp_check_bl:
    # Convert bl to lowercase
    cmpb $'A', %bl
    jb .strcasecmp_compare
    cmpb $'Z', %bl
    ja .strcasecmp_compare
    addb $32, %bl
.strcasecmp_compare:
    cmpb %bl, %al
    jne .strcasecmp_diff
    testb %al, %al
    jz .strcasecmp_equal
    incq %rdi
    incq %rsi
    jmp .strcasecmp_loop
.strcasecmp_diff:
    movzbq %al, %rax
    movzbq %bl, %rbx
    subq %rbx, %rax
    jmp .strcasecmp_end
.strcasecmp_equal:
    xorq %rax, %rax
.strcasecmp_end:
    popq %rbp
    ret

# rindex implementation
.globl rindex
rindex:
    pushq %rbp
    movq %rsp, %rbp
    xorq %rax, %rax
.rindex_loop:
    movb (%rdi), %dl
    cmpb %sil, %dl
    jne .rindex_check_end
    movq %rdi, %rax
.rindex_check_end:
    testb %dl, %dl
    jz .rindex_end
    incq %rdi
    jmp .rindex_loop
.rindex_end:
    popq %rbp
    ret

# strstr implementation
.globl strstr
strstr:
    pushq %rbp
    movq %rsp, %rbp
    pushq %rbx
    pushq %rcx
    pushq %rdx
    cmpb $0, (%rsi)
    je .strstr_return_haystack
.strstr_outer_loop:
    movb (%rdi), %al
    testb %al, %al
    jz .strstr_not_found
    cmpb (%rsi), %al
    jne .strstr_next_char
    movq %rdi, %rbx
    movq %rsi, %rcx
.strstr_inner_loop:
    movb (%rbx), %al
    movb (%rcx), %dl
    testb %dl, %dl
    jz .strstr_found
    testb %al, %al
    jz .strstr_not_found
    cmpb %dl, %al
    jne .strstr_next_char
    incq %rbx
    incq %rcx
    jmp .strstr_inner_loop
.strstr_found:
    movq %rdi, %rax
    jmp .strstr_end
.strstr_next_char:
    incq %rdi
    jmp .strstr_outer_loop
.strstr_return_haystack:
    movq %rdi, %rax
    jmp .strstr_end
.strstr_not_found:
    xorq %rax, %rax
.strstr_end:
    popq %rdx
    popq %rcx
    popq %rbx
    popq %rbp
    ret

# strpbrk implementation
.globl strpbrk
strpbrk:
    pushq %rbp
    movq %rsp, %rbp
    pushq %rbx
    pushq %rcx
.strpbrk_outer_loop:
    movb (%rdi), %al
    testb %al, %al
    jz .strpbrk_not_found
    movq %rsi, %rbx
.strpbrk_inner_loop:
    movb (%rbx), %cl
    testb %cl, %cl
    jz .strpbrk_next_char
    cmpb %cl, %al
    je .strpbrk_found
    incq %rbx
    jmp .strpbrk_inner_loop
.strpbrk_found:
    movq %rdi, %rax
    jmp .strpbrk_end
.strpbrk_next_char:
    incq %rdi
    jmp .strpbrk_outer_loop
.strpbrk_not_found:
    xorq %rax, %rax
.strpbrk_end:
    popq %rcx
    popq %rbx
    popq %rbp
    ret

# strcspn implementation
.globl strcspn
strcspn:
    pushq %rbp
    movq %rsp, %rbp
    pushq %rbx
    pushq %rcx
    xorq %rax, %rax
.strcspn_outer_loop:
    movb (%rdi,%rax), %dl
    testb %dl, %dl
    jz .strcspn_end
    movq %rsi, %rbx
.strcspn_inner_loop:
    movb (%rbx), %cl
    testb %cl, %cl
    jz .strcspn_next_char
    cmpb %cl, %dl
    je .strcspn_end
    incq %rbx
    jmp .strcspn_inner_loop
.strcspn_next_char:
    incq %rax
    jmp .strcspn_outer_loop
.strcspn_end:
    popq %rcx
    popq %rbx
    popq %rbp
    ret

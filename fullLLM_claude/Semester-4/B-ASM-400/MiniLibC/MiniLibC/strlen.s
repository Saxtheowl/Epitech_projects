.section .text
.globl strlen

# size_t strlen(const char *s);
# Input: rdi = pointer to string
# Output: rax = length of string
strlen:
    pushq %rbp
    movq %rsp, %rbp
    
    xorq %rax, %rax        # Initialize counter to 0
    
.loop:
    cmpb $0, (%rdi,%rax)   # Check if current char is null terminator
    je .end                # If yes, jump to end
    incq %rax              # Increment counter
    jmp .loop              # Continue loop
    
.end:
    popq %rbp
    ret
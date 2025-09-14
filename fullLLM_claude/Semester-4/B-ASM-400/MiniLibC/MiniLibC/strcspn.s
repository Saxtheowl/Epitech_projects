BITS 64

section .text
global strcspn

; size_t strcspn(const char *s, const char *reject);
; Input: rdi = s, rsi = reject
; Output: rax = length of initial segment of s which consists entirely of characters not in reject
strcspn:
    push rbp
    mov rbp, rsp
    push rbx
    push rcx
    
    xor rax, rax        ; Initialize counter to 0
    
.outer_loop:
    mov dl, byte [rdi + rax]  ; Load character from s at position rax
    test dl, dl         ; Check if end of s
    jz .end             ; If end, return current count
    
    mov rbx, rsi        ; Reset reject pointer for each character in s
    
.inner_loop:
    mov cl, byte [rbx]  ; Load character from reject
    test cl, cl         ; Check if end of reject
    jz .next_char       ; If end of reject, character is not in reject, continue
    cmp dl, cl          ; Compare characters
    je .end             ; If match found, return current count
    inc rbx             ; Move to next character in reject
    jmp .inner_loop
    
.next_char:
    inc rax             ; Increment counter
    jmp .outer_loop
    
.end:
    pop rcx
    pop rbx
    pop rbp
    ret
BITS 64

section .text
global strpbrk

; char *strpbrk(const char *s, const char *accept);
; Input: rdi = s, rsi = accept
; Output: rax = pointer to first character in s that matches any character in accept, or NULL
strpbrk:
    push rbp
    mov rbp, rsp
    push rbx
    push rcx
    
.outer_loop:
    mov al, byte [rdi]  ; Load character from s
    test al, al         ; Check if end of s
    jz .not_found       ; If end, no match found
    
    mov rbx, rsi        ; Reset accept pointer for each character in s
    
.inner_loop:
    mov cl, byte [rbx]  ; Load character from accept
    test cl, cl         ; Check if end of accept
    jz .next_char       ; If end of accept, try next character in s
    cmp al, cl          ; Compare characters
    je .found           ; If match, return current position
    inc rbx             ; Move to next character in accept
    jmp .inner_loop
    
.found:
    mov rax, rdi        ; Return pointer to matching character
    jmp .end
    
.next_char:
    inc rdi             ; Move to next character in s
    jmp .outer_loop
    
.not_found:
    xor rax, rax        ; Return NULL
    
.end:
    pop rcx
    pop rbx
    pop rbp
    ret
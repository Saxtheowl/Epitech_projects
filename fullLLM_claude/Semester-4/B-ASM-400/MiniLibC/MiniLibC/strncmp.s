BITS 64

section .text
global strncmp

; int strncmp(const char *s1, const char *s2, size_t n);
; Input: rdi = s1, rsi = s2, rdx = n
; Output: rax = difference between first differing characters
strncmp:
    push rbp
    mov rbp, rsp
    
    test rdx, rdx       ; Check if n == 0
    jz .equal           ; If n == 0, strings are considered equal
    
.loop:
    mov al, byte [rdi]  ; Load character from s1
    mov bl, byte [rsi]  ; Load character from s2
    cmp al, bl          ; Compare characters
    jne .diff           ; If different, jump to diff
    test al, al         ; Check if end of string
    jz .equal           ; If both strings ended, they're equal
    inc rdi             ; Move s1 pointer
    inc rsi             ; Move s2 pointer
    dec rdx             ; Decrement counter
    jnz .loop           ; Continue if counter != 0
    
.equal:
    xor rax, rax        ; Return 0 (strings are equal or n bytes compared)
    jmp .end
    
.diff:
    movzx rax, al       ; Zero-extend al to rax
    movzx rbx, bl       ; Zero-extend bl to rbx
    sub rax, rbx        ; Calculate difference
    
.end:
    pop rbp
    ret
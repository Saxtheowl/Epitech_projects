BITS 64

section .text
global strchr

; char *strchr(const char *s, int c);
; Input: rdi = pointer to string, rsi = character to find
; Output: rax = pointer to first occurrence of c in s, or NULL
strchr:
    push rbp
    mov rbp, rsp
    
.loop:
    mov al, byte [rdi]  ; Load current character
    cmp al, sil         ; Compare with target character (sil = low byte of rsi)
    je .found           ; If match, return current position
    test al, al         ; Check if end of string (null terminator)
    jz .not_found       ; If end of string, return NULL
    inc rdi             ; Move to next character
    jmp .loop
    
.found:
    mov rax, rdi        ; Return pointer to found character
    jmp .end
    
.not_found:
    xor rax, rax        ; Return NULL
    
.end:
    pop rbp
    ret
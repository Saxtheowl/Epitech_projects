BITS 64

section .text
global rindex

; char *rindex(const char *s, int c);
; Input: rdi = pointer to string, rsi = character to find
; Output: rax = pointer to last occurrence of c in s, or NULL
rindex:
    push rbp
    mov rbp, rsp
    
    xor rax, rax        ; Initialize result to NULL
    
.loop:
    mov dl, byte [rdi]  ; Load current character
    cmp dl, sil         ; Compare with target character (sil = low byte of rsi)
    jne .check_end      ; If no match, check if end of string
    mov rax, rdi        ; Update result to current position (last match found)
    
.check_end:
    test dl, dl         ; Check if end of string (null terminator)
    jz .end             ; If end of string, return last match or NULL
    inc rdi             ; Move to next character
    jmp .loop
    
.end:
    pop rbp
    ret
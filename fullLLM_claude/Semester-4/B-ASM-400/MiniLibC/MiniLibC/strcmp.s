BITS 64

section .text
global strcmp

; int strcmp(const char *s1, const char *s2);
; Input: rdi = s1, rsi = s2
; Output: rax = difference between first differing characters
strcmp:
    push rbp
    mov rbp, rsp
    
.loop:
    mov al, byte [rdi]  ; Load character from s1
    mov bl, byte [rsi]  ; Load character from s2
    cmp al, bl          ; Compare characters
    jne .diff           ; If different, jump to diff
    test al, al         ; Check if end of string
    jz .equal           ; If both strings ended, they're equal
    inc rdi             ; Move s1 pointer
    inc rsi             ; Move s2 pointer
    jmp .loop
    
.diff:
    movzx rax, al       ; Zero-extend al to rax
    movzx rbx, bl       ; Zero-extend bl to rbx  
    sub rax, rbx        ; Calculate difference
    jmp .end
    
.equal:
    xor rax, rax        ; Return 0 (strings are equal)
    
.end:
    pop rbp
    ret
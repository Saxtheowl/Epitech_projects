BITS 64

section .text
global strcasecmp

; int strcasecmp(const char *s1, const char *s2);
; Input: rdi = s1, rsi = s2
; Output: rax = difference between first differing characters (case-insensitive)
strcasecmp:
    push rbp
    mov rbp, rsp
    
.loop:
    mov al, byte [rdi]  ; Load character from s1
    mov bl, byte [rsi]  ; Load character from s2
    
    ; Convert al to lowercase
    cmp al, 'A'
    jb .check_bl
    cmp al, 'Z'
    ja .check_bl
    add al, 32          ; Convert to lowercase
    
.check_bl:
    ; Convert bl to lowercase
    cmp bl, 'A'
    jb .compare
    cmp bl, 'Z'
    ja .compare
    add bl, 32          ; Convert to lowercase
    
.compare:
    cmp al, bl          ; Compare characters (now both lowercase)
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
BITS 64

section .text
global memmove

; void *memmove(void *dest, const void *src, size_t n);
; Input: rdi = dest, rsi = src, rdx = n
; Output: rax = dest
memmove:
    push rbp
    mov rbp, rsp
    
    mov rax, rdi        ; Save original dest pointer for return
    test rdx, rdx       ; Check if n == 0
    jz .end             ; If n == 0, return immediately
    
    ; Check if src < dest (need to copy backwards to avoid overlap issues)
    cmp rsi, rdi
    jb .copy_forward    ; If src < dest, copy forward
    
    ; Copy backwards (from end to beginning)
    add rdi, rdx        ; Point to end of dest
    add rsi, rdx        ; Point to end of src
    dec rdi             ; Point to last byte
    dec rsi             ; Point to last byte
    
.copy_backward:
    mov cl, byte [rsi]  ; Load byte from source
    mov byte [rdi], cl  ; Store byte to destination
    dec rdi             ; Move dest pointer backward
    dec rsi             ; Move src pointer backward
    dec rdx             ; Decrement counter
    jnz .copy_backward  ; Continue if counter != 0
    jmp .end
    
.copy_forward:
    mov cl, byte [rsi]  ; Load byte from source
    mov byte [rdi], cl  ; Store byte to destination
    inc rdi             ; Move dest pointer
    inc rsi             ; Move src pointer
    dec rdx             ; Decrement counter
    jnz .copy_forward   ; Continue if counter != 0
    
.end:
    pop rbp
    ret
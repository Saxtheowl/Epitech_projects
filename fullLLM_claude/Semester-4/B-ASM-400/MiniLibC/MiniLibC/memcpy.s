BITS 64

section .text
global memcpy

; void *memcpy(void *dest, const void *src, size_t n);
; Input: rdi = dest, rsi = src, rdx = n
; Output: rax = dest
memcpy:
    push rbp
    mov rbp, rsp
    
    mov rax, rdi        ; Save original dest pointer for return
    test rdx, rdx       ; Check if n == 0
    jz .end             ; If n == 0, return immediately
    
.loop:
    mov cl, byte [rsi]  ; Load byte from source
    mov byte [rdi], cl  ; Store byte to destination
    inc rdi             ; Move dest pointer
    inc rsi             ; Move src pointer
    dec rdx             ; Decrement counter
    jnz .loop           ; Continue if counter != 0
    
.end:
    pop rbp
    ret
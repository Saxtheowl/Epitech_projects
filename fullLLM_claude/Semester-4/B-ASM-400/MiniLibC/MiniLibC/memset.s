BITS 64

section .text
global memset

; void *memset(void *s, int c, size_t n);
; Input: rdi = pointer to memory, rsi = value to set, rdx = number of bytes
; Output: rax = pointer to memory (same as rdi)
memset:
    push rbp
    mov rbp, rsp
    
    mov rax, rdi        ; Save original pointer for return
    test rdx, rdx       ; Check if n == 0
    jz .end             ; If n == 0, return immediately
    
.loop:
    mov byte [rdi], sil ; Set byte to value (sil = low byte of rsi)
    inc rdi             ; Move to next byte
    dec rdx             ; Decrement counter
    jnz .loop           ; Continue if counter != 0
    
.end:
    pop rbp
    ret
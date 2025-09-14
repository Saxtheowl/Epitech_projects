BITS 64

section .text
global strstr

; char *strstr(const char *haystack, const char *needle);
; Input: rdi = haystack, rsi = needle
; Output: rax = pointer to first occurrence of needle in haystack, or NULL
strstr:
    push rbp
    mov rbp, rsp
    push rbx
    push rcx
    push rdx
    
    ; Check if needle is empty
    cmp byte [rsi], 0
    je .return_haystack ; Empty needle matches at beginning
    
.outer_loop:
    mov al, byte [rdi]  ; Load character from haystack
    test al, al         ; Check if end of haystack
    jz .not_found       ; If end, needle not found
    
    cmp al, byte [rsi]  ; Compare with first character of needle
    jne .next_char      ; If no match, try next character
    
    ; Potential match found, check the rest
    mov rbx, rdi        ; Save haystack position
    mov rcx, rsi        ; Save needle position
    
.inner_loop:
    mov al, byte [rbx]  ; Load character from haystack
    mov dl, byte [rcx]  ; Load character from needle
    test dl, dl         ; Check if end of needle
    jz .found           ; If end of needle, we found a match
    test al, al         ; Check if end of haystack
    jz .not_found       ; If end of haystack but not end of needle, no match
    cmp al, dl          ; Compare characters
    jne .next_char      ; If no match, try next position in haystack
    inc rbx             ; Move to next character in haystack
    inc rcx             ; Move to next character in needle
    jmp .inner_loop
    
.found:
    mov rax, rdi        ; Return pointer to match
    jmp .end
    
.next_char:
    inc rdi             ; Move to next character in haystack
    jmp .outer_loop
    
.return_haystack:
    mov rax, rdi        ; Return haystack (empty needle)
    jmp .end
    
.not_found:
    xor rax, rax        ; Return NULL
    
.end:
    pop rdx
    pop rcx
    pop rbx
    pop rbp
    ret
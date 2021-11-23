extern printf

section .data

section .text
    global B


B:
    push rbp
    mov rax, 0x1234567812345678
    xor ax, 0x11
    lea rdi, [format]
    mov rsi, rax
    call printf
    xor rax, 0x11
    mov rdi, format
    mov rsi, rax
    call printf
    pop rbp
    format: db "%llx",0

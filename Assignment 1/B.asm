extern C
section .data
    msg db "-----------", 10, " Entered B", 10, "-----------", 10

section .text
    global B

B:
    call _enterB
    call _printASCII
    call _exitC

_enterB:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg
    mov rdx, 35
    syscall
    ret

_printASCII:
    push rbp
    mov rbp, rsp

    ;ror rsp, 32

    mov rax, 1
    mov rdi, 1
    mov rsi, rbp
    mov rdx, 40
    syscall

    mov rsp, rbp
    pop rbp
    ret     

_exitC:
    call C
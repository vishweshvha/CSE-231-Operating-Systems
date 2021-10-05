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
    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 32
    syscall
    ret     

_exitC: 
    push C
    ret
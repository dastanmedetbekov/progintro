section .text
    global _start

calculate:
    add al, bl

    ret

_start:
    

    mov eax, 1
    mov ebx, 0
    int 0x80

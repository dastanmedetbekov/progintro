section .bss
    result resd 1

section .data
    newline db 10

section .text
    global _start

    default rel
print:
    mov     [result],   eax
    xor     eax,    eax
    mov     rax,    1
    mov     rdi,    1
    mov     rsi,    result
    mov     rdx,    4
    syscall
;    mov     rax,    1
;   mov     rdi,    1
;    mov     rsi,    newline
;    mov     rdx,    1
;    syscall
    ret

   

_start:
    mov     eax,    4f682bh
    mov     ax,     19005
    mov     al,     130o
    call print ; first task aka (a)
; b
    mov     eax,    99f6eeh
    mov     ax,     63172o
    mov     al,     99
    call print
; c
    mov     eax,    0db9fe3h
    mov     ax,     2486
    mov     ah,     5bh  
    call print ;
; d
    mov     eax,    $7f2176
    mov     ax,     62877
    mov     al,     134o
    call print ;
; e
    mov     eax,    0x55623b
    mov     ax,     31071
    mov     ah,     0c9h
    call print ;
; f
    mov     eax,    5e1bdah
    mov     ax,     45102
    mov     al,     $40
    call print ;


    ; exit
    mov     rax,    60
    xor     rdi,    rdi
    syscall
    

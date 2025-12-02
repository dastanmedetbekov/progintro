global	num2hex

section .bss

buffer		resb 16
buflen		equ $-buffer

section	.text
num2hex:	; in: eax = num
		; out: eax = addr. of the string
		push ebp
		mov ebp, esp
		push esi


		lea esi, [buffer + buflen - 1]
		mov byte [esi], 0
		dec esi

		cmp eax, 0
		jnz .notzero
		mov byte [esi], '0'	; zero from the start
		jmp short .quit

.notzero:
.lp:		mov cl, al
		and cl, 0x0f
		cmp cl, 9
		jg .hexdig		; at least A
		add cl, '0'		; arabic dig., turn into dig. code
		jmp short .dig_done
.hexdig:	add cl, 'A'-10		; hex dig., turn info letter code
.dig_done:	mov [esi], cl
		shr eax, 4
		cmp eax, 0
		je .quit
		dec esi
		jmp short .lp

.quit:		mov eax, esi
		pop esi
		mov esp, ebp
		pop ebp
		ret

global	hex2num

section	.text
hex2num:	; arg1 == address of the string
		; in case of error, ECX == 0x80..00, CF is set
		push ebp
		mov ebp, esp
		xor eax, eax		; result accumulator
		mov ecx, [ebp+8]	; arg1
.lp:		mov dl, byte [ecx]
		cmp dl, 0
		jz .quit_ok
		cmp dl, '0'
		jl .notdig
		cmp dl, '9'
		jg .notdig
		sub dl, '0'		; it's a digit '0'..'9'
		jmp short .addit
.notdig:	cmp dl, 'a'
		jl .notlower
		cmp dl, 'f'
		jg .notlower
		sub dl, 'a'-10		; it's a lowercase 'a'..'f'
		jmp short .addit
.notlower:	cmp dl, 'A'
		jl .errchar
		cmp dl, 'F'
		jg .errchar
		sub dl, 'A'-10		; it's an uppercase 'A'..'F'
.addit:		shl eax, 4
		and dl, 0fh
		or al, dl
		inc ecx
		jmp short .lp
.errchar:	mov eax, 080000000h	; let it be error value
		stc
		jmp .quit
.quit_ok:	clc
.quit:		mov esp, ebp
		pop ebp
		ret

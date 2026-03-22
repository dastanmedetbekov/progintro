
global	flagshow
extern	putstr

section	.text


zfmsg		db "ZF: ", 0
ofmsg		db "OF: ", 0
cfmsg		db "CF: ", 0
sfmsg		db "SF: ", 0
flgset		db "1    ", 0
flgunset	db "0    ", 0
newline		db 10,0

%macro		PRFLAG 2	; jnX, Xfmsg
		push dword %2
		call putstr
		add esp, 4
		push esi
		popfd
		%1 %%notset
		push dword flgset
		call putstr
		add esp, 4
		jmp %%done
%%notset:	push dword flgunset
		call putstr
		add esp, 4
%%done:		nop
%endmacro



flagshow:			; arg1 = the flags (pushed by pushf)
		push ebp
		mov ebp, esp
		push esi
		mov esi, [ebp+8]
		PRFLAG jnz, zfmsg
		PRFLAG jns, sfmsg
		PRFLAG jno, ofmsg
		PRFLAG jnc, cfmsg
		push dword newline
		call putstr
		add esp, 4
		pop esi
		mov esp, ebp
		pop ebp
		ret

%include "kernel.inc"

global		_start

extern		quit
extern		putstr
extern		hex2num
extern		num2hex
extern		flagshow


section		.text

_start:		mov ebp, esp
		cmp dword [ebp], 3
		je .args_ok
		mov eax, msg_help
		jmp message_and_quit
.args_ok:

		mov eax, [ebp+8]
		push eax
		call hex2num
		add esp, 4
		mov esi, eax
		mov eax, [ebp+12]
		push eax
		call hex2num
		add esp, 4
		mov ecx, esi
		mov ch, al		; now CX contains both bytes
		mov esi, ecx		; we store them in ESI

		mov eax, esi
		call num2hex
		push eax
		call putstr
		add esp, 4
		push dword newln
		call putstr
		add esp, 4

%macro OP_AND_PRINT 2  ; %1 = message, %2 = add/sub
		push dword %1
		call putstr
		add esp, 4
		mov eax, esi
		%2 al, ah
		pushfd				;;; used later by flagshow
		and eax, 0xff
		call num2hex
		push eax
		call putstr
		add esp, 4
		push dword spc4
		call putstr
		add esp, 4
		call flagshow
		add esp, 4
%endmacro

		OP_AND_PRINT msg_doingadd, add
		OP_AND_PRINT msg_doingsub, sub

        	; quit
		jmp quit


msg_help	db 'Usage: flags <al> <ah> (both in hex)', 10, 0

msg_doingadd	db 'doing ADD AL, AH:    ', 0
msg_doingsub	db 'doing SUB AL, AH:    ', 0

newln		db 10, 0
spc4		db "    ", 0

;; in: eax = message_id
message_and_quit:
		push eax
		call putstr
		jmp quit

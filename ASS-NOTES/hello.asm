; x86 Assembly
global _start

section .text:

_start:
	mov eax, 0x4		; use the write syscall
	mov ebx, 1		; use stdout as the fd
	mov ecx, message
	mov edx, message_lenght
	int 0x80		; invoke syscall
	
	;			exit
	mov eax, 0x1
	mov ebx, 0
	int 0x80

section .data:
	message: db "Hello World!", 0xA
	message_lenght equ $-message

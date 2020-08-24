section .text
global _start
_start:
		mov r8, 10
		mov r8, 100
		mov r8, 1000
		mov r8, -12
		mov r8, -200

		mov rax, 10
		mov rax, 100
		mov rax, 1000
		mov rax, -12
		mov rax, -200

		mov r8, 10
		mov r9, 10
		mov r10, 10
		mov r11, 10
		mov r12, 10
		mov r13, 10
		mov r14, 10
		mov r15, 10
		
		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h

section .data
		number times 10 db 0
		db 0
		sign db 0
		number_new times 10 db 0
		db 0
		number_rev times 10 db 0
		sqrt_from dq 0
		sqrt_res  dq 0
		SYMB_POINT equ 2

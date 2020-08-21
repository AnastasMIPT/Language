section .text
global _start
_start:
		call main

		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h



main:
		push rbp
		mov rbp, rsp

		;04 = 00 000 100
		;0c = 00 001 100
		;14 = 00 010 100


		;25 = 00 100 101
		mov qword [sqrt_from], rax
		mov qword [sqrt_from], rcx
		mov qword [sqrt_from], rdx
		mov qword [sqrt_from], rbx
		mov qword [sqrt_from], rbp
		mov qword [sqrt_from], rsp
		mov qword [sqrt_from], rsi
		mov qword [sqrt_from], rdi
		nop
		nop
		finit
		fild qword [sqrt_from]
		fsqrt
		fistp qword [sqrt_res]
		nop
		nop
		mov rax, qword [sqrt_from]
		mov rcx, qword [sqrt_from]
		mov rdx, qword [sqrt_from]
		mov rbx, qword [sqrt_from]
		mov rbp, qword [sqrt_from]
		mov rsp, qword [sqrt_from]
		mov rsi, qword [sqrt_from]
		mov rdi, qword [sqrt_from]
		
		
		imul rax, 10

		mov qword [number], 100

		mov rsp, rbp
		pop rbp
		ret





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
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
		
		
		
		
		
		imul rax, rax
		imul rax, rcx
		imul rax, rdx
		imul rax, rbx
		imul rax, rsp
		imul rax, rbp
		imul rax, rsi
		imul rax, rdi
		
		nop
		nop
		nop

		imul r10, r8
		imul rax, r9
		imul rax, r10
		imul rax, r11
		imul rax, r12
		imul rax, r13
		imul rax, r14
		imul rax, r15
		nop
		nop
		nop

		imul rcx, rax
		imul rcx, rcx
		imul rcx, rdx
		imul rcx, rbx
		nop
		nop
		nop
		imul rcx, r8
		imul rcx, r9
		imul rcx, r10
		imul rcx, r11
		nop
		nop
		nop

		imul rdx, rax
		imul rdx, rcx
		imul rdx, rdx
		imul rdx, rbx
		nop
		nop
		nop

		imul rbx, rax
		imul rbx, rcx
		imul rbx, rdx
		imul rbx, rbx
		nop
		nop
		nop


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
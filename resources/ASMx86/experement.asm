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

		cmp rax, rax
		cmp rax, rcx
		cmp rax, rdx
		cmp rax, rbx
		cmp rax, rsp
		cmp rax, rbp
		cmp rax, rsi
		cmp rax, rdi
		mov rax, rdi

		nop
		nop
		nop

		cmp rcx, rax
		cmp rcx, rcx
		cmp rcx, rdx
		cmp rcx, rbx
		cmp rcx, rsp
		cmp rcx, rbp
		cmp rcx, rsi
		cmp rcx, rdi

		nop
		nop
		nop

		cmp rdx, rax
		cmp rdx, rcx
		cmp rdx, rdx
		cmp rdx, rbx
		cmp rdx, rsp
		cmp rdx, rbp
		cmp rdx, rsi
		cmp rdx, rdi
		

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
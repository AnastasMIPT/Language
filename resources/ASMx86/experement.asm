section .text
global _start
_start:
		
		sub rax, rax
		sub rax, rcx
		sub rax, rdx
		sub rax, rbx
		sub rax, rbp
		sub rax, rsp
		sub rax, rdi
		sub rax, rsi
		nop
		nop
		nop

		sub rax, rax
		sub rax, rcx
		sub rax, rdx
		sub rax, rbx
		sub rax, rbp
		sub rax, rsp
		sub rax, rdi
		sub rax, rsi
		
		nop
		nop
		nop



		sub rcx, rax
		sub rcx, rcx
		sub rcx, rdx
		sub rcx, rbx
		sub rcx, rbp
		sub rcx, rsp
		sub rcx, rdi
		sub rcx, rsi
		
		nop
		nop
		nop

		add rcx, rax
		add rcx, rcx
		add rcx, rdx
		add rcx, rbx
		add rcx, rbp
		add rcx, rsp
		add rcx, rdi
		add rcx, rsi
		
		nop
		nop
		nop


		sub rcx, -10
		sub rcx, -20
		sub rcx, -30
		sub rcx, -40
		sub rcx, -50
		sub rcx, -60
		sub rcx, -70
		sub rcx, -80


		nop
		nop
		nop


		sub rcx, 1
		sub rcx, 2
		sub rcx, 3
		sub rcx, 4
		sub rcx, 5
		sub rcx, 6
		sub rcx, 7
		sub rcx, 8


		mov rcx, 1
		mov rcx, 2
		mov rcx, 3
		mov rcx, 4
		mov rcx, 5
		mov rcx, 6
		mov rcx, 7
		mov rcx, 8

		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h

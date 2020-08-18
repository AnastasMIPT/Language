section .text
global _start
_start:
		
		add rax, rax
		add rcx, rax
		add rdx, rax
		add rbx, rax
		add rsp, rax
		add rbp, rax
		add rsi, rax
		add rdi, rax
		

		nop
		nop
		nop


		add rax, rcx
		add rcx, rcx
		add rdx, rcx
		add rbx, rcx
		add rsp, rcx
		add rbp, rcx
		add rsi, rcx
		add rdi, rcx


		nop
		nop
		nop


		add rax, rdx
		add rcx, rdx
		add rdx, rdx
		add rbx, rdx
		add rsp, rdx
		add rbp, rdx
		add rsi, rdx
		add rdi, rdx
		

		nop
		nop
		nop


		add rax, rax
		add rax, rcx
		add rax, rdx
		add rax, rbx
		add rax, rsp
		add rax, rbp
		add rax, rsi
		add rax, rdi


		nop
		nop
		nop


		add rcx, rax
		add rcx, rcx
		add rcx, rdx
		add rcx, rbx
		add rcx, rsp
		add rcx, rbp
		add rcx, rsi
		add rcx, rdi

		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h


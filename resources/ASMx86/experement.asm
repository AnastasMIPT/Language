section .text
global _start
_start:
		
		add rax, [rbp-1]
		add rax, [rbp-2]
		add rax, [rbp-3]
		add rax, [rbp-4]
		add rax, [rbp-5]
		add rax, [rbp-6]
		add rax, [rbp-7]
		add rax, [rbp-8]



		mov rax, [rbp-1]
		mov rax, [rbp-2]
		mov rax, [rbp-3]
		mov rax, [rbp-4]
		mov rax, [rbp-5]
		mov rax, [rbp-6]
		mov rax, [rbp-7]
		mov rax, [rbp-8]
		

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


		add rcx, [rbp+1]
		add rcx, [rbp+2]
		add rcx, [rbp+3]
		add rcx, [rbp+4]
		add rcx, [rbp+5]
		add rcx, [rbp+6]
		add rcx, [rbp+7]
		add rcx, [rbp+8]


		nop
		nop
		nop


		add rcx, [rbp+100]
		add rcx, [rbp+200]
		add rcx, [rbp+300]
		add rcx, [rbp+400]
		add rcx, [rbp+500]
		add rcx, [rbp+600]
		add rcx, [rbp+700]
		add rcx, [rbp+800]


		mov rcx, [rbp+100]
		mov rcx, [rbp+200]
		mov rcx, [rbp+300]
		mov rcx, [rbp+400]
		mov rcx, [rbp+500]
		mov rcx, [rbp+600]
		mov rcx, [rbp+700]
		mov rcx, [rbp+800]

		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h


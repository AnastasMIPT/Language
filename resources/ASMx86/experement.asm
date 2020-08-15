section .text
global _start
_start:
		
		mov rax, [rbp-1]
		mov rax, [rbp-2]
		mov rax, [rbp-3]
		mov rax, [rbp-4]
		mov rax, [rbp-5]
		mov rax, [rbp-6]
		mov rax, [rbp-7]
		mov rax, [rbp-8]
		mov rax, [rbp-9]
		mov rax, [rbp-10]


		nop
		nop
		nop

		mov rax, [rbp+100]
		mov rax, [rbp+200]
		mov rax, [rbp+300]
		mov rax, [rbp+400]
		mov rax, [rbp+5000]
		mov rax, [rbp+60000]
		mov rax, [rbp+3000000000]
		mov rax, [rbp+8]
		mov rax, [rbp+9]
		mov rax, [rbp+10]

		nop
		nop
		nop

		mov rcx, [rbp+1]
		mov rcx, [rbp+2]
		mov rcx, [rbp+3]
		mov rcx, [rbp+4]
		mov rcx, [rbp+5]
		mov rcx, [rbp+6]
		mov rcx, [rbp+7]
		mov rcx, [rbp+8]
		mov rcx, [rbp+9]
		mov rcx, [rbp+10]
		
		nop
		nop
		nop

		mov rdx, [rbp+1]
		mov rdx, [rbp+2]
		mov rdx, [rbp+3]
		mov rdx, [rbp+4]
		mov rdx, [rbp+5]
		mov rdx, [rbp+6]
		mov rdx, [rbp+7]
		mov rdx, [rbp+8]
		mov rdx, [rbp+9]
		mov rdx, [rbp+10]

		
		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h


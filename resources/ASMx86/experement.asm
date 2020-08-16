section .text
global _start
_start:
		
		mov rax, qword -1
		mov rcx, qword -2
		mov rdx, qword -3
		mov rbx, qword 2000000000
		mov rsp, qword -35000000
		mov rbp, qword -35000000
		mov rdi, qword 1234
		mov rsi, qword 12
		mov rax, qword 900
		mov rax, qword 3000
		mov rax, qword 123
		mov rax, qword 134
		mov rax, qword 23
		mov rax, qword 1
		mov rax, qword 345


		nop
		nop
		nop

		mov rcx, 123
		mov rcx, 1234
		mov rcx, 12
		mov rcx, 900
		mov rcx, 3000
		mov rcx, 123
		mov rcx, 134
		mov rcx, 23
		mov rcx, 1
		mov rcx, 345


		nop
		nop
		nop


		mov rdx, 123
		mov rdx, 1234
		mov rdx, 12
		mov rdx, 900
		mov rdx, 3000
		mov rdx, 123
		mov rdx, 134
		mov rdx, 23
		mov rdx, 1
		mov rdx, 345


		nop
		nop
		nop
		
		
		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h


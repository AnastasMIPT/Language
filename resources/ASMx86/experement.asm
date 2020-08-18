section .text
global _start
_start:
		
		push rax
		push rcx
		push rdx
		push rbx
		push rsp
		push rbp
		push rsi
		push rdi
		
		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h


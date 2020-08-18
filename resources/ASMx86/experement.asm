section .text
global _start
_start:
		
		pop rax
		pop rcx
		pop rdx
		pop rbx
		pop rsp
		pop rbp
		pop rsi
		pop rdi
		
		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h


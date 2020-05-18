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
		mov qword [rbp-4], qword 3
		mov rax, qword 1
		add rax, qword [rbp-4]
		mov qword [rbp-8], rax
		mov rsp, rbp
		pop rbp
		ret


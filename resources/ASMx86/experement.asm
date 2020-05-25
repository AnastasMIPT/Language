section .text
global _start
_start:
		nop
		nop
		nop
		push rbp
		mov rbp, rsp
		nop
		nop
		nop


		mov rbx, [rbp-8]
		mov rbx, [rbp-16]
		mov rbx, [rbp-24]
		mov rbx, [rbp-32]

		nop

		mov rcx, [rbp-8]
		mov rcx, [rbp-16]
		mov rcx, [rbp-24]
		mov rcx, [rbp-32]
				
		




		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h

section .data                           
		number times 10 db 0 
		db 0
		sign db 0
		number_new times 10 db 0
		db 0
		number_rev times 10 db 0
		sqrt_from dq 0
		sqrt_res  dq 0
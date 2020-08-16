section .text
global _start
_start:
		
		mov qword [rbp-1], 123
		mov qword [rbp-2], 1234
		mov qword [rbp-3], 12
		mov qword [rbp-4], 900
		mov qword [rbp-5], 3000
		mov qword [rbp-6], 123
		mov qword [rbp-7], 134
		mov qword [rbp-8], 23
		mov qword [rbp-9], 1
		mov qword [rbp-10], 345


		nop
		nop
		nop

		
		nop

		mov qword [rbp+100], 123
		mov qword [rbp+200], 13 
		mov qword [rbp+300], 98
		mov qword [rbp+400], -2323
		mov qword [rbp+5000], 12 
		mov qword [rbp+60], 3443
		mov qword [rbp+30], 12
		mov qword [rbp+8], 12 
		mov qword [rbp+9], 3456 
		mov qword [rbp+10], 123 

		nop
		nop
		nop

		
		
		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h


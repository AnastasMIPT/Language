section .text
global _start
_start:
		
		push qword [rbp]
		push qword [rbp-1]
		push qword [rbp-2]
		push qword [rbp-3]
		push qword [rbp-4]
		push qword [rbp+1]
		push qword [rbp+2]
		push qword [rbp+3]
		push qword [rbp+4]


		push qword [rbp+127]
		push qword [rbp+128]

		push qword [rbp+129]
		push qword [rbp-129]
		push qword [rbp-127]
		push qword [rbp-128]



		push qword [rbp+2000000000]
		push qword [rbp-2000000000]


		nop
		nop
		nop
		
		push qword [rbp]
		push qword [rbp+1]
		push qword [rbp+2]
		push qword [rbp+3]
		push qword [rbp+4]
		
		
		
		push qword 123
		push qword 12
		push qword 10
		push qword -12341
		
		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h


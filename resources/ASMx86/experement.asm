section .text
global _start
_start:
		


		push qword 1
		push qword 2
		push qword 3
		push qword 4



		push qword 123
		push qword 12
		push qword 10
		push qword -12341

		push qword -1
		push qword -2
		push qword -3
		push qword -4


		push qword 100
		push qword 200
		push qword 300
		push qword 400
		
		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h


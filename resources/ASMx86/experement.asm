section .text
global _start
_start:
		
		add rax, 100
		add rax, 200
		add rax, 300
		add rax, 400
		add rax, 500
		add rax, 600
		add rax, 700
		add rax, 800

		nop
		nop
		nop

		add rcx, 100
		add rcx, 200
		add rcx, 300
		add rcx, 400
		add rcx, 500
		add rcx, 600
		add rcx, 700
		add rcx, 800
		
		nop
		nop
		nop

		add rdx, 100
		add rdx, 200
		add rdx, 300
		add rdx, 400
		add rdx, 500
		add rdx, 600
		add rdx, 700
		add rdx, 800
		
		nop
		nop
		nop


		add rcx, -10
		add rcx, -20
		add rcx, -30
		add rcx, -40
		add rcx, -50
		add rcx, -60
		add rcx, -70
		add rcx, -80


		nop
		nop
		nop


		add rcx, 1
		add rcx, 2
		add rcx, 3
		add rcx, 4
		add rcx, 5
		add rcx, 6
		add rcx, 7
		add rcx, 8


		mov rcx, 1
		mov rcx, 2
		mov rcx, 3
		mov rcx, 4
		mov rcx, 5
		mov rcx, 6
		mov rcx, 7
		mov rcx, 8

		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h


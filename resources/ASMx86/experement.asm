section .text
global _start
_start:
		
		sub rax, 100
		sub rcx, 2
		sub rdx, 3
		sub rbx, 4
		sub rax, 100

		sub rax, 200
		sub rax, 300
		sub rax, 400
		sub rax, 500
		sub rax, 600
		sub rax, 700
		sub rax, 800

		nop
		nop
		nop

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




		sub rcx, 100
		sub rcx, 200
		sub rcx, 300
		sub rcx, 400
		sub rcx, 500
		sub rcx, 600
		sub rcx, 700
		sub rcx, 800
		
		nop
		nop
		nop

		sub rdx, 100
		sub rdx, 200
		sub rdx, 300
		sub rdx, 400
		sub rdx, 500
		sub rdx, 600
		sub rdx, 700
		sub rdx, 800
		
		nop
		nop
		nop


		sub rcx, -10
		sub rcx, -20
		sub rcx, -30
		sub rcx, -40
		sub rcx, -50
		sub rcx, -60
		sub rcx, -70
		sub rcx, -80


		nop
		nop
		nop


		sub rcx, 1
		sub rcx, 2
		sub rcx, 3
		sub rcx, 4
		sub rcx, 5
		sub rcx, 6
		sub rcx, 7
		sub rcx, 8


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

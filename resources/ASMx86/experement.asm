section .text
global _start
_start:
		
		sub rax, [rbp-100]
		sub rcx, [rbp-2]
		sub rdx, [rbp-3]
		sub rbx, [rbp-4]
		
		sub rax, [rbp-100]
		sub rax, [rbp-200]
		sub rax, [rbp-300]
		sub rax, [rbp-400]
		sub rax, [rbp-500]
		sub rax, [rbp-600]
		sub rax, [rbp-700]
		sub rax, [rbp-800]

		nop
		nop
		nop

		add rax, [rbp-100]
		add rax, [rbp-200]
		add rax, [rbp-300]
		add rax, [rbp-400]
		add rax, [rbp-500]
		add rax, [rbp-600]
		add rax, [rbp-700]
		add rax, [rbp-800]

		nop
		nop
		nop




		sub rcx, [rbp-100]
		sub rcx, [rbp-200]
		sub rcx, [rbp-300]
		sub rcx, [rbp-400]
		sub rcx, [rbp-500]
		sub rcx, [rbp-600]
		sub rcx, [rbp-700]
		sub rcx, [rbp-800]
		
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

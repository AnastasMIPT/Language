section .text
global _start
_start:
		call main

		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h
factorial:
		push rbp
		mov rbp, rsp
		sub rsp, 0

; _R->left->num -0.000000
		mov rcx, qword [rbp+16]
		mov rdx, qword 100
		cmp rcx, rdx
		jne end_if0

		;return

		mov rcx, qword 100
		mov rax, rcx

		mov rsp, rbp
		pop rbp
		ret

end_if0:

		;return


		;call $$

		mov rcx, qword [rbp+16]
		sub rcx, qword 100
		push qword rcx
		call factorial
		add rsp, 8
		mov rcx, rax


		mov rax, rcx
		mov r15 , 100
		cqo
		idiv r15
		mov qword rcx, rax

		mov rdx, qword [rbp+16]
		imul rcx, rdx
		mov rax, rcx

		mov rsp, rbp
		pop rbp
		ret

main:
		push rbp
		mov rbp, rsp
		sub rsp, 16

; _R->left->num 2.000000

		;input


		mov rax, 3
		mov rbx, 2
		mov rcx, number
		mov rdx, 10
		int 80h
		push qword number
		call atoi
		sub rsp, 8
		imul rax, 100
		mov qword [rbp-8], rax

		;assign

		;call $$

		push qword [rbp-8]
		call factorial
		add rsp, 8
		mov qword [rbp-16], rax



		;output

		mov rbx, qword [rbp-16]
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h


		;return

		mov rax, rcx

		mov rsp, rbp
		pop rbp
		ret

itoa:
		push rbp
		mov rbp, rsp
		xor rax, rax
		mov rax, qword [rbp+16]
		mov rbx, qword number_rev
		mov rdi, number_new
		xor r10, r10
		or rax, rax
		jns .Loop
		neg rax
		mov byte [rdi], '-'
		inc rbx
		inc rdi
.Loop:
		xor rdx, rdx
		mov r8, 0ah
		div r8
		add rdx, '0'
		mov byte [rbx+r10], dl
		inc r10
		cmp qword r10, SYMB_POINT
		jne .NoPoint
		mov byte [rbx+r10], '.'
		inc r10
.NoPoint:
		cmp rax, 0
		je .Loop2
		jmp .Loop
.Loop2:		;writing reversev
		dec r10
		mov al, [rbx+r10]
		stosb
		cmp r10, 0
		je .Exit
		jmp .Loop2
.Exit:

		mov byte [rdi+1], 10
		mov rsp, rbp
		pop rbp
		ret
atoi:
		push rbp
		mov rbp, rsp
		xor rax, rax

		mov byte [sign], 0
		mov rbx, qword [rbp+16]
		xor rcx, rcx
		cmp byte [rbx], '-'
		jne .Next
		mov byte [sign], 1
		inc rbx
.Next:
		cmp byte [rbx], 10
		je .Exit
		mov cl, byte [rbx]
		sub rcx, '0'
		imul rax, 10
		add rax, rcx
		inc rbx
		jmp .Next
.Exit:
		cmp byte[sign], 1
		jne .Exit_l
		neg rax
.Exit_l:
		mov rsp, rbp
		pop rbp
		ret
section .data
		number times 10 db 0
		db 0
		sign db 0
		number_new times 10 db 0
		db 0
		number_rev times 10 db 0
		sqrt_from dq 0
		sqrt_res  dq 0
		SYMB_POINT equ 2

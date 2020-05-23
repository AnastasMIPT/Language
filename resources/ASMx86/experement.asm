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
		sub rsp, 24


		mov rax, 3
		mov rbx, 2
		mov rcx, number
		mov rdx, 10
		int 80h
		push qword number
		call atoi
		sub rsp, 8
		mov qword [rbp-8], rax


		mov rax, 3
		mov rbx, 2
		mov rcx, number
		mov rdx, 10
		int 80h
		push qword number
		call atoi
		sub rsp, 8
		mov qword [rbp-16], rax

		mov rax, qword [rbp-8]
		cqo
		idiv qword [rbp-16]
		mov rbx, rax
		mov qword [rbp-24], rbx

		push qword [rbp-24]
		mov rbx, qword [rbp-16]
		add rbx, qword [rbp-8]
		push qword rbx
		call sum
		add rsp, 16
		mov rbx, rax

		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h
		mov rax, qword 0

		mov rsp, rbp
		pop rbp
		ret

sum:
		push rbp
		mov rbp, rsp
		sub rsp, 8

		mov qword [rbp-8], 5
		mov rax, qword [rbp+24]
		add rax, qword [rbp+16]

		mov rsp, rbp
		pop rbp
		ret

mul:
		push rbp
		mov rbp, rsp
		sub rsp, 8

		mov qword [rbp-8], 5
		mov rax, qword [rbp+24]
		imul rax, qword [rbp+16]

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
		db 0

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
		sub rsp, 64


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
		mov qword [rbp-16], rax


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
		mov qword [rbp-24], rax

		;assign
		mov qword [rbp-32], 0


		mov rbx, qword [rbp-8]
		mov rcx, qword 0
		cmp rbx, rcx
		jne end_if0
		;assign

		;call

		push qword [rbp-24]
		push qword [rbp-16]
		call linear
		add rsp, 16
		mov qword [rbp-32], rax



		;output

		mov rbx, qword [rbp-32]
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h


		;return

		mov rax, rbx

		mov rsp, rbp
		pop rbp
		ret

end_if0:
		mov rbx, qword [rbp-16]
		mov rcx, qword 0
		cmp rbx, rcx
		jne end_if1
		mov rbx, qword 0
		mov rcx, qword [rbp-24]
		cmp rbx, rcx
		jg end_if2
		mov rbx, qword 0
		mov rcx, qword [rbp-8]
		cmp rbx, rcx
		jg end_if3

		;output

		mov rbx, qword 0
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h


		;return

		mov rax, rbx

		mov rsp, rbp
		pop rbp
		ret

end_if3:

		;output

		mov rbx, qword 200
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h

		;assign

		;sqrt

		mov rbx, qword [rbp-24]
		imul rbx, qword -1
		mov rcx, qword [rbp-8]

		mov rax, rcx
		mov r15 , 100
		cqo
		idiv r15
		mov qword rcx, rax

		mov rax, rbx
		cqo
		idiv rcx
		mov rbx, rax

		mov qword [sqrt_from], rbx
		finit
		fild qword [sqrt_from]
		fsqrt
		fistp qword [sqrt_res]
		mov rbx, qword [sqrt_res]

		imul rbx, 10
		mov qword [rbp-40], rbx



		;output

		mov rbx, qword [rbp-40]
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h


		;output

		mov rbx, qword [rbp-40]
		imul rbx, qword -1
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h


		;return

		mov rax, rbx

		mov rsp, rbp
		pop rbp
		ret

end_if2:
		mov rbx, qword 0
		mov rcx, qword [rbp-8]
		cmp rbx, rcx
		jg end_if4

		;output

		mov rbx, qword 200
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h

		;assign

		;sqrt

		mov rbx, qword [rbp-24]
		imul rbx, qword -1
		mov rcx, qword [rbp-8]

		mov rax, rcx
		mov r15 , 100
		cqo
		idiv r15
		mov qword rcx, rax

		mov rax, rbx
		cqo
		idiv rcx
		mov rbx, rax

		mov qword [sqrt_from], rbx
		finit
		fild qword [sqrt_from]
		fsqrt
		fistp qword [sqrt_res]
		mov rbx, qword [sqrt_res]

		imul rbx, 10
		mov qword [rbp-40], rbx



		;output

		mov rbx, qword [rbp-40]
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h


		;output

		mov rbx, qword [rbp-40]
		imul rbx, qword -1
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h


		;return

		mov rax, rbx

		mov rsp, rbp
		pop rbp
		ret

end_if4:

		;output

		mov rbx, qword 0
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h


		;return

		mov rax, rbx

		mov rsp, rbp
		pop rbp
		ret

end_if1:
		;assign

		;call

		push qword [rbp-24]
		push qword [rbp-16]
		push qword [rbp-8]
		call diskriminant
		add rsp, 24
		mov qword [rbp-48], rax


		mov rbx, qword 0
		mov rcx, qword [rbp-48]
		cmp rbx, rcx
		jg end_if5
		;assign
		mov rbx, qword 0
		sub rbx, qword [rbp-16]

		;sqrt

		mov rcx, qword [rbp-48]

		mov qword [sqrt_from], rcx
		finit
		fild qword [sqrt_from]
		fsqrt
		fistp qword [sqrt_res]
		mov rcx, qword [sqrt_res]

		imul rcx, 10
		add rbx, rcx
		mov rcx, qword [rbp-8]
		imul rcx, qword 2

		mov rax, rcx
		mov r15 , 100
		cqo
		idiv r15
		mov qword rcx, rax

		mov rax, rbx
		cqo
		idiv rcx
		mov rbx, rax
		mov qword [rbp-56], rbx


		;assign
		mov rbx, qword 0
		sub rbx, qword [rbp-16]

		;sqrt

		mov rcx, qword [rbp-48]

		mov qword [sqrt_from], rcx
		finit
		fild qword [sqrt_from]
		fsqrt
		fistp qword [sqrt_res]
		mov rcx, qword [sqrt_res]

		imul rcx, 10
		sub rbx, rcx
		mov rcx, qword [rbp-8]
		imul rcx, qword 2

		mov rax, rcx
		mov r15 , 100
		cqo
		idiv r15
		mov qword rcx, rax

		mov rax, rbx
		cqo
		idiv rcx
		mov rbx, rax
		mov qword [rbp-64], rbx



		;output

		mov rbx, qword 200
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h


		;output

		mov rbx, qword [rbp-56]
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h


		;output

		mov rbx, qword [rbp-64]
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h


		;return

		mov rax, rbx

		mov rsp, rbp
		pop rbp
		ret

end_if5:
		mov rbx, qword [rbp-48]
		mov rcx, qword 0
		cmp rbx, rcx
		jne end_if6

		;output

		mov rbx, qword 100
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h


		;output

		mov rbx, qword 0
		mov rcx, qword [rbp-16]
		mov rdi, qword [rbp-8]
		imul rdi, qword 2

		mov rax, rdi
		mov r15 , 100
		cqo
		idiv r15
		mov qword rdi, rax

		mov rax, rcx
		cqo
		idiv rdi
		mov rcx, rax
		sub rbx, rcx
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h


		;return

		mov rax, rbx

		mov rsp, rbp
		pop rbp
		ret

end_if6:

		;output

		mov rbx, qword 0
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h


		;return

		mov rax, rbx

		mov rsp, rbp
		pop rbp
		ret

diskriminant:
		push rbp
		mov rbp, rsp
		sub rsp, 0


		;return

		mov rbx, qword [rbp+24]
		mov rcx, qword [rbp+24]

		mov rax, rbx
		mov r15 , 100
		cqo
		idiv r15
		mov qword rbx, rax

		imul rbx, rcx
		mov rcx, qword [rbp+16]
		imul rcx, qword 4
		mov rdi, qword [rbp+32]

		mov rax, rcx
		mov r15 , 100
		cqo
		idiv r15
		mov qword rcx, rax

		imul rcx, rdi
		sub rbx, rcx
		mov rax, rbx

		mov rsp, rbp
		pop rbp
		ret

linear:
		push rbp
		mov rbp, rsp
		sub rsp, 0

		mov rbx, qword [rbp+16]
		mov rcx, qword 0
		cmp rbx, rcx
		jne end_if7
		mov rbx, qword [rbp+24]
		mov rcx, qword 0
		cmp rbx, rcx
		je end_if8

		;return

		mov rbx, qword 0
		mov rax, rbx

		mov rsp, rbp
		pop rbp
		ret

end_if8:

		;return

		mov rbx, qword -100
		mov rax, rbx

		mov rsp, rbp
		pop rbp
		ret

end_if7:

		;output

		mov rbx, qword 100
		push rbx
		call itoa
		sub rsp, 8

		mov rax, 4
		mov rbx, 1
		mov rcx, number_new
		mov rdx, 11
		int 80h


		;return

		mov rbx, qword 0
		mov rcx, qword [rbp+24]
		mov rdi, qword [rbp+16]

		mov rax, rdi
		mov r15 , 100
		cqo
		idiv r15
		mov qword rdi, rax

		mov rax, rcx
		cqo
		idiv rdi
		mov rcx, rax
		sub rbx, rcx
		mov rax, rbx

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

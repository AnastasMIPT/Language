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
		sub rsp, 48

; _R->left->num 6.000000

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


		mov rcx, qword [rbp-8]
		mov rdx, qword 0
		cmp rcx, rdx
		jne end_if0
		;assign

		;call $$

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

		mov rax, rcx

		mov rsp, rbp
		pop rbp
		ret

end_if0:
		mov rcx, qword [rbp-16]
		mov rdx, qword 0
		cmp rcx, rdx
		jne end_if1
		mov rcx, qword 0
		mov rdx, qword [rbp-24]
		cmp rcx, rdx
		jg end_if2
		mov rcx, qword 0
		mov rdx, qword [rbp-8]
		cmp rcx, rdx
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

		mov rax, rcx

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

		mov rcx, qword [rbp-24]
		imul rcx, qword -1
		mov rdx, qword [rbp-8]

		mov rax, rdx
		mov r15 , 100
		cqo
		idiv r15
		mov qword rdx, rax

		mov rax, rcx
		cqo
		idiv rdx
		mov rcx, rax

		mov qword [sqrt_from], rcx
		finit
		fild qword [sqrt_from]
		fsqrt
		fistp qword [sqrt_res]
		mov rcx, qword [sqrt_res]

		imul rcx, 10
		mov qword [rbp-40], rcx



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

		mov rax, rcx

		mov rsp, rbp
		pop rbp
		ret

end_if2:
		mov rcx, qword 0
		mov rdx, qword [rbp-8]
		cmp rcx, rdx
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

		mov rcx, qword [rbp-24]
		imul rcx, qword -1
		mov rdx, qword [rbp-8]

		mov rax, rdx
		mov r15 , 100
		cqo
		idiv r15
		mov qword rdx, rax

		mov rax, rcx
		cqo
		idiv rdx
		mov rcx, rax

		mov qword [sqrt_from], rcx
		finit
		fild qword [sqrt_from]
		fsqrt
		fistp qword [sqrt_res]
		mov rcx, qword [sqrt_res]

		imul rcx, 10
		mov qword [rbp-40], rcx



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

		mov rax, rcx

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

		mov rax, rcx

		mov rsp, rbp
		pop rbp
		ret

end_if1:
		;assign

		;call $$

		push qword [rbp-24]
		push qword [rbp-16]
		push qword [rbp-8]
		call diskriminant
		add rsp, 24
		mov qword [rbp-48], rax


		mov rcx, qword 0
		mov rdx, qword [rbp-48]
		cmp rcx, rdx
		jg end_if5

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


		;sqrt

		mov rbx, qword [rbp-48]

		mov qword [sqrt_from], rbx
		finit
		fild qword [sqrt_from]
		fsqrt
		fistp qword [sqrt_res]
		mov rbx, qword [sqrt_res]

		imul rbx, 10
		sub rbx, qword [rbp-16]
		mov rsi, qword [rbp-8]
		imul rsi, qword 2

		mov rax, rsi
		mov r15 , 100
		cqo
		idiv r15
		mov qword rsi, rax

		mov rax, rbx
		cqo
		idiv rsi
		mov rbx, rax
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

		;sqrt

		mov rsi, qword [rbp-48]

		mov qword [sqrt_from], rsi
		finit
		fild qword [sqrt_from]
		fsqrt
		fistp qword [sqrt_res]
		mov rsi, qword [sqrt_res]

		imul rsi, 10
		sub rbx, rsi
		sub rbx, qword [rbp-16]
		mov rsi, qword [rbp-8]
		imul rsi, qword 2

		mov rax, rsi
		mov r15 , 100
		cqo
		idiv r15
		mov qword rsi, rax

		mov rax, rbx
		cqo
		idiv rsi
		mov rbx, rax
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

end_if5:
		mov rcx, qword [rbp-48]
		mov rdx, qword 0
		cmp rcx, rdx
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
		mov rsi, qword [rbp-16]
		mov rdi, qword [rbp-8]
		imul rdi, qword 2

		mov rax, rdi
		mov r15 , 100
		cqo
		idiv r15
		mov qword rdi, rax

		mov rax, rsi
		cqo
		idiv rdi
		mov rsi, rax
		sub rbx, rsi
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

		mov rax, rcx

		mov rsp, rbp
		pop rbp
		ret

diskriminant:
		push rbp
		mov rbp, rsp
		sub rsp, 0

; _R->left->num -0.000000

		;return

		mov rcx, qword [rbp+24]

		mov rax, rcx
		mov r15 , 100
		cqo
		idiv r15
		mov qword rcx, rax

		mov rdx, qword [rbp+24]
		imul rcx, rdx
		mov rdx, qword [rbp+16]
		imul rdx, qword 4

		mov rax, rdx
		mov r15 , 100
		cqo
		idiv r15
		mov qword rdx, rax

		mov rbx, qword [rbp+32]
		imul rdx, rbx
		sub rcx, rdx
		mov rax, rcx

		mov rsp, rbp
		pop rbp
		ret

linear:
		push rbp
		mov rbp, rsp
		sub rsp, 0

; _R->left->num -0.000000
		mov rcx, qword [rbp+16]
		mov rdx, qword 0
		cmp rcx, rdx
		jne end_if7
		mov rcx, qword [rbp+24]
		mov rdx, qword 0
		cmp rcx, rdx
		je end_if8

		;return

		mov rcx, qword 0
		mov rax, rcx

		mov rsp, rbp
		pop rbp
		ret

end_if8:

		;return

		mov rcx, qword -100
		mov rax, rcx

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

		mov rcx, qword 0
		mov rdx, qword [rbp+24]
		mov rbx, qword [rbp+16]

		mov rax, rbx
		mov r15 , 100
		cqo
		idiv r15
		mov qword rbx, rax

		mov rax, rdx
		cqo
		idiv rbx
		mov rdx, rax
		sub rcx, rdx
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

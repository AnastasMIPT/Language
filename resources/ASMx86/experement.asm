%include "printf.asm"

section .text
global _start
_start:
		;call main

		mov rax, 3
   		mov rbx, 2
   		mov rcx, number  
   		mov rdx, 11          ;5 bytes (numeric, 1 for sign) of that information
   		int 80h

		; push qword strin
		; call printf

		push qword number
		call atoi
		sub rsp, 8

		add rax, 1
		

		push rax
		push qword format
		call printf
		add rsp, 16

		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h
main:
		push rbp
		mov rbp, rsp
		sub rsp, 32

		mov qword [rbp-8], 3
		mov qword [rbp-16], 4
		mov rax, qword [rbp-8]
		cqo
		idiv qword [rbp-16]
		mov rbx, rax
		mov qword [rbp-24], rbx
		mov rbx, qword [rbp-16]
		add rbx, qword [rbp-8]
		mov rcx, qword 5
		add rcx, qword [rbp-16]
		cmp rbx, rcx
		jg end_if0

		push qword [rbp-16]
		push qword [rbp-8]
		call mul
		add rsp, 16
		mov qword [rbp-32], rax
end_if0:
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

section .data                           ;Data segment
    number times 10 db 0
	db 0
	sign db 0
    format db '%d'
    db 0ah, 0

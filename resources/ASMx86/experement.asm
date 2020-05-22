%include "printf.asm"

section .text
global _start
_start:
		;call main

;		mov rax, 3
 ;  		mov rbx, 2
  ; 		mov rcx, num  
   ;		mov rdx, 5          ;5 bytes (numeric, 1 for sign) of that information
   	;	int 80h

		xor rax, rax
		push qword num
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

.Next:		
		cmp byte [rbx], 0
		je .Exit
		mov cl, byte [rbx]
		sub rcx, '0'
		imul rax, 10
		add rax, rcx
		inc rbx
		jmp .Next

.Exit:
		mov rsp, rbp
		pop rbp
		ret


itoa:
		push rbp
		mov rbp, rsp

		xor rax, rax
		mov rax, qword [rbp+16]
		mov rbx, qword num
		xor r10, r10

.Loop:				
		xor rdx, rdx							;RDX = 0
		
		mov r8, 0ah								;R8 = 10
		div r8									;EAX = EAX / 10, EDX = EAX % 10
		add rdx, '0'							;EDX += 48
		
		mov byte [rbx+r10], dl					    ;int_rezult[R10] = dl
		inc r10						        ;R10++
		
		cmp rax, 0								;if (AX == 0) break
		je .Exit
		jmp .Loop

.Exit:
		mov rsp, rbp
		pop rbp
		ret

section .data                           ;Data segment
    num db 0, 0, 0, 0
	db 0
    lennum equ $-num
    format db 'gghgj %d'
    db 0ah, 0

    str10 db 'Is it true?', 0
	number db '123', 0
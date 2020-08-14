section .text
global _start
_start:
		
		mov rax, rax
		mov rax, rcx
		mov rax, rdx
		mov rax, rbx
		mov rax, rsp
		mov rax, rbp
		mov rax, rsi
		mov rax, rdi
		
		
		mov eax, eax
		mov eax, ecx
		mov eax, edx
		mov eax, ebx
		mov eax, esp
		mov eax, ebp
		mov eax, esi
		mov eax, edi
		
		nop
		nop
		nop
		
		mov rcx, rax
		mov rcx, rcx
		mov rcx, rdx
		mov rcx, rbx
		mov rcx, rsp
		mov rcx, rbp
		mov rcx, rsi
		mov rcx, rdi
		
		nop
		nop
		nop
		
		mov rdx, rax
		mov rdx, rcx
		mov rdx, rdx
		mov rdx, rbx
		mov rdx, rsp
		mov rdx, rbp
		mov rdx, rsi
		mov rdx, rdi
		
		
		nop
		nop
		nop
		
		mov rbx, rax
		mov rbx, rcx
		mov rbx, rdx
		mov rbx, rbx
		mov rbx, rsp
		mov rbx, rbp
		mov rbx, rsi
		mov rbx, rdi
		
		
		
		mov rax, [rbp - 4]
		mov rax, [rbp - 8]
		mov rax, [rbp - 16]

		mov rax, 1           ; номер системного вызова  sys_exit
		mov rbx, 0           ; код завершения программы
		int 80h


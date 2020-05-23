#ifndef LANGUAGE_FUNC_H
#define LANGUAGE_FUNC_H

#endif //LANGUAGE_FUNC_H


constexpr char itoa_s[] =    
"itoa:\n"                                        
"\t\tpush rbp\n"                                  
"\t\tmov rbp, rsp\n"                              
"\t\txor rax, rax\n"                              
"\t\tmov rax, qword [rbp+16]\n"                   
"\t\tmov rbx, qword number_rev\n"                 
"\t\tmov rdi, number_new\n"                       
"\t\txor r10, r10\n"                              
"\t\tor rax, rax\n"                               
"\t\tjns .Loop\n"								
"\t\tneg rax\n"									   
"\t\tmov byte [rdi], '-'\n"						
"\t\tinc rbx\n"									
"\t\tinc rdi\n"		                        
".Loop:\n"	                                
"\t\txor rdx, rdx\n"						
"\t\tmov r8, 0ah\n"							
"\t\tdiv r8\n"									
"\t\tadd rdx, '0'\n"							
"\t\tmov byte [rbx+r10], dl\n"                    
"\t\tinc r10\n"
"\t\tcmp qword r10, SYMB_POINT\n"
"\t\tjne .NoPoint\n"
"\t\tmov byte [rbx+r10], '.'\n"
"\t\tinc r10\n"
".NoPoint:\n"	                                 
"\t\tcmp rax, 0\n"                               
"\t\tje .Loop2\n"                                 
"\t\tjmp .Loop\n"                                 
".Loop2:		;writing reversev\n"             
"\t\tdec r10\n"                                  
"\t\tmov al, [rbx+r10]\n"                         
"\t\tstosb\n"                                     
"\t\tcmp r10, 0\n"                                
"\t\tje .Exit\n"                                  
"\t\tjmp .Loop2\n"                                
".Exit:\n\n"                                      
"\t\tmov byte [rdi+1], 10\n"                      
"\t\tmov rsp, rbp\n"                              
"\t\tpop rbp\n"                                 
"\t\tret\n";

constexpr char atoi_s[] =
"atoi:\n"
"\t\tpush rbp\n"
"\t\tmov rbp, rsp\n"
"\t\txor rax, rax\n\n"
"\t\tmov byte [sign], 0\n"
"\t\tmov rbx, qword [rbp+16]\n"
"\t\txor rcx, rcx\n"
"\t\tcmp byte [rbx], '-'\n"
"\t\tjne .Next\n"
"\t\tmov byte [sign], 1\n"
"\t\tinc rbx\n"
".Next:\n"		
"\t\tcmp byte [rbx], 10\n"
"\t\tje .Exit\n"
"\t\tmov cl, byte [rbx]\n"
"\t\tsub rcx, '0'\n"
"\t\timul rax, 10\n"
"\t\tadd rax, rcx\n"
"\t\tinc rbx\n"
"\t\tjmp .Next\n"
".Exit:\n"
"\t\tcmp byte[sign], 1\n"
"\t\tjne .Exit_l\n"
"\t\tneg rax\n"
".Exit_l:\n"
"\t\tmov rsp, rbp\n"
"\t\tpop rbp\n"
"\t\tret\n"
"section .data\n"                           
"\t\tnumber times 10 db 0\n" 
"\t\tdb 0\n" 
"\t\tsign db 0\n" 
"\t\tnumber_new times 10 db 0\n"
"\t\tdb 0\n"
"\t\tnumber_rev times 10 db 0\n";

constexpr char output_s[] =
"\t\tpush rbx\n"
"\t\tcall itoa\n"
"\t\tsub rsp, 8\n\n"
"\t\tmov rax, 4\n"
"\t\tmov rbx, 1\n"
"\t\tmov rcx, number_new\n"
"\t\tmov rdx, 11\n"
"\t\tint 80h\n";

constexpr char input_s[] =
 "\n\t\tmov rax, 3\n"
"\t\tmov rbx, 2\n"
"\t\tmov rcx, number\n" 
"\t\tmov rdx, 10\n"
"\t\tint 80h\n"
"\t\tpush qword number\n"
"\t\tcall atoi\n"
"\t\tsub rsp, 8\n";

constexpr char start_s[] =
"section .text\n"
"global _start\n"
"_start:\n"
"\t\tcall main\n\n"
"\t\tmov rax, 1           ; номер системного вызова  sys_exit\n"
"\t\tmov rbx, 0           ; код завершения программы\n"
"\t\tint 80h\n";

constexpr char ret_s[] =
"\n\t\tmov rsp, rbp\n"
"\t\tpop rbp\n"
"\t\tret\n\n";
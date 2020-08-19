#ifndef LANGUAGE_FUNC_H
#define LANGUAGE_FUNC_H

#endif //LANGUAGE_FUNC_H

constexpr unsigned long long SizeOdDataSeg = 64;
constexpr unsigned int SizeItoa = 121;
constexpr unsigned int SizeOutput = 37;
constexpr unsigned int SizeGStart = 17;

constexpr unsigned char g_start_b[] = {
0xe8, 0xd4, 0x00, 0x00, 0x00,       	                    // callq  0x400189
0xb8, 0x01, 0x00, 0x00, 0x00,       	                    // mov    $0x1,%eax
0xbb, 0x00, 0x00, 0x00, 0x00,       	                    // mov    $0x0,%ebx
0xcd, 0x80                	                                // int    $0x80
};

constexpr unsigned char itoa_b[] = {   
0x55,                   	                                // push   %rbp
0x48, 0x89, 0xe5,             	                            // mov    %rsp,%rbp
0x48, 0x31, 0xc0,             	                            // xor    %rax,%rax
0x48, 0x8b, 0x45, 0x10,          	                        // mov    0x10(%rbp),%rax
0x48, 0xbb, 0xbf, 0x01, 0x60, 0x00, 0x00, 	                // movabs $0x6001bf,%rbx
0x00, 0x00, 0x00, 
0x48, 0xbf, 0xb4, 0x01, 0x60, 0x00, 0x00, 	                // movabs $0x6001b4,%rdi
0x00, 0x00, 0x00, 
0x4d, 0x31, 0xd2,             	                            // xor    %r10,%r10
0x48, 0x09, 0xc0,             	                            // or     %rax,%rax
0x79, 0x0c,                	                                // jns    0x4000f4
0x48, 0xf7, 0xd8,             	                            // neg    %rax
0xc6, 0x07, 0x2d,             	                            // movb   $0x2d,(%rdi)
0x48, 0xff, 0xc3,             	                            // inc    %rbx
0x48, 0xff, 0xc7,             	                            // inc    %rdi
0x48, 0x31, 0xd2,             	                            // xor    %rdx,%rdx
0x41, 0xb8, 0x0a, 0x00, 0x00, 0x00,    	                    // mov    $0xa,%r8d
0x49, 0xf7, 0xf0,             	                            // div    %r8
0x48, 0x83, 0xc2, 0x30,          	                        // add    $0x30,%rdx
0x42, 0x88, 0x14, 0x13,          	                        // mov    %dl,(%rbx,%r10,1)
0x49, 0xff, 0xc2,             	                            // inc    %r10
0x49, 0x83, 0xfa, 0x02,          	                        // cmp    $0x2,%r10
0x75, 0x08,                	                                // jne    0x400119
0x42, 0xc6, 0x04, 0x13, 0x2e,       	                    // movb   $0x2e,(%rbx,%r10,1)
0x49, 0xff, 0xc2,             	                            // inc    %r10
0x48, 0x83, 0xf8, 0x00,          	                        // cmp    $0x0,%rax
0x74, 0x02,                	                                // je     0x400121
0xeb, 0xd3,                	                                // jmp    0x4000f4
0x49, 0xff, 0xca,             	                            // dec    %r10
0x42, 0x8a, 0x04, 0x13,          	                        // mov    (%rbx,%r10,1),%al
0xaa,                  	                                    // stos   %al,%es:(%rdi)
0x49, 0x83, 0xfa, 0x00,         	                        // cmp    $0x0,%r10
0x74, 0x02,                	                                // je     0x400131
0xeb, 0xf0,                	                                // jmp    0x400121
0xc6, 0x47, 0x01, 0x0a,          	                        // movb   $0xa,0x1(%rdi)
0x48, 0x89, 0xec,             	                            // mov    %rbp,%rsp
0x5d,                  	                                    // pop    %rbp
0xc3                   	                                // retq   
};

constexpr unsigned char atoi_b[] = {
0x55,                   	                                // push   %rbp
0x48, 0x89, 0xe5,             	                            // mov    %rsp,%rbp
0x48, 0x31, 0xc0,             	                            // xor    %rax,%rax
0xc6, 0x04, 0x25, 0xb3, 0x01, 0x60, 0x00, 	                // movb   $0x0,0x6001b3
0x00, 
0x48, 0x8b, 0x5d, 0x10,          	                        // mov    0x10(%rbp),%rbx
0x48, 0x31, 0xc9,             	                            // xor    %rcx,%rcx
0x80, 0x3b, 0x2d,             	                            // cmpb   $0x2d,(%rbx)
0x75, 0x0b,                	                                // jne    0x400160
0xc6, 0x04, 0x25, 0xb3, 0x01, 0x60, 0x00, 	                // movb   $0x1,0x6001b3
0x01, 
0x48, 0xff, 0xc3,             	                            // inc    %rbx
0x80, 0x3b, 0x0a,             	                            // cmpb   $0xa,(%rbx)
0x74, 0x12,                	                                // je     0x400177
0x8a, 0x0b,                	                                // mov    (%rbx),%cl
0x48, 0x83, 0xe9, 0x30,          	                        // sub    $0x30,%rcx
0x48, 0x6b, 0xc0, 0x0a,          	                        // imul   $0xa,%rax,%rax
0x48, 0x01, 0xc8,             	                            // add    %rcx,%rax
0x48, 0xff, 0xc3,             	                            // inc    %rbx
0xeb, 0xe9,                	                                // jmp    0x400160
0x80, 0x3c, 0x25, 0xb3, 0x01, 0x60, 0x00, 	                // cmpb   $0x1,0x6001b3
0x01, 
0x75, 0x03,                	                                // jne    0x400184
0x48, 0xf7, 0xd8,             	                            // neg    %rax
0x48, 0x89, 0xec,             	                            // mov    %rbp,%rsp
0x5d,                   	                                // pop    %rbp
0xc3,                   	                                // retq   
0x55,                   	                                // push   %rbp
0x48, 0x89, 0xe5,             	                            // mov    %rsp,%rbp
0x48, 0x83, 0xec, 0x08,          	                        // sub    $0x8,%rsp
0x48, 0xc7, 0x45, 0xf8, 0xf4, 0x01, 0x00, 	                // movq   $0x1f4,-0x8(%rbp)
0x00};

constexpr char data_b[SizeOdDataSeg] = {};

constexpr unsigned char output_b[] = {
0x53,                   	                    // push   %rbx
0xe8, 0x1e, 0xff, 0xff, 0xff,       	        // callq  0x4000c1
0x48, 0x83, 0xec, 0x08,          	            // sub    $0x8,%rsp
0xb8, 0x04, 0x00, 0x00, 0x00,       	        // mov    $0x4,%eax
0xbb, 0x01, 0x00, 0x00, 0x00,       	        // mov    $0x1,%ebx
0x48, 0xb9, 0xdc, 0x01, 0x60, 0x00, 0x00, 	    // movabs $0x6001dc,%rcx
0x00, 0x00, 0x00, 
0xba, 0x0b, 0x00, 0x00, 0x00,       	        // mov    $0xb,%edx
0xcd, 0x80};                	                // int    $0x80


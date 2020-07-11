#ifndef ELF_H
#define ELF_H

#include <cstdio>
#include <memory>
#include "Commands.h"

typedef unsigned char      BYTE;
typedef unsigned short int WORD;
typedef unsigned int       DWORD;
typedef unsigned long long QWORD;

constexpr DWORD PF_X = 1;
constexpr DWORD PF_W = 2;
constexpr DWORD PF_R = 4;


constexpr unsigned long long SizeOdDataSegm = 64;
constexpr unsigned int SizeOfELF_header =  SizeOdDataSegm + 304;


    



#pragma pack (push, 1)
struct ELF_Header {
    const DWORD  EI_MAG       = 0x464c457f;          // .ELF
    const BYTE   EI_CLASS     = 0x02;                // 64-bit format
    const BYTE   EI_DATA      = 0x01;                // LittleEndian
    const BYTE   EI_VERSION   = 1;
    const BYTE   EI_OSABI     = 0x00;                // System-V
    const QWORD  reserved     = 0;
    const WORD   e_type       = 2;                   // ELF_EXEC
    const WORD   e_machine    = 0x003e;              // amd64
    const DWORD  e_version    = 1;                   // Original ELF
    const QWORD  e_entry      = 0x400170;            // virtual point of entry
    const QWORD  e_phoff      = 0x40;                // Program header offset
    const QWORD  e_shoff      = 0x0b0;               // Section header offset
    const DWORD  e_flags      = 0x00;                // Processor flags
    const WORD   e_ehsize     = 64;                  // ElfHeaderSize
    const WORD   e_phentsize  = 56;                  // Program header size
    const WORD   e_phnum      = 2;                   // Num of Program headers
    const WORD   e_shentsize  = 64;                  // Section header size
    const WORD   e_shnum      = 2;                   // Num of Section headers
    const WORD   e_shstrndx   = 0;                   // shstrtab

};
#pragma pack (pop)




#pragma pack (push, 1)
struct Program_Header {
    const DWORD  p_type;     
    const DWORD  p_flags;        // segment flags
    const QWORD  p_offset;       //Offset segment from start of file
    const QWORD  p_vaddr;
    const QWORD  p_paddr;
    const QWORD  p_filesz;
    const QWORD  p_memsz;
    const QWORD  p_align;
    constexpr Program_Header (const DWORD  _p_type,  const DWORD  _p_flags, const QWORD  _p_offset,
                              const QWORD  _p_vaddr, const QWORD  _p_paddr, const QWORD  _p_filesz,
                              const QWORD  _p_memsz, const QWORD  _p_align) 
    :   p_type  (_p_type),  p_flags  (_p_flags), p_offset (_p_offset), p_vaddr (_p_vaddr),
        p_paddr (_p_paddr), p_filesz (_p_filesz), p_memsz (_p_memsz),  p_align (_p_align) {}

};
#pragma pack (pop)

#pragma pack (push, 1)
struct Section_Header {
    const DWORD  sh_name;   
    const DWORD  sh_type;    
    const QWORD  sh_flags;   
    const QWORD  sh_addr;
    const QWORD  sh_offset;
    const QWORD  sh_size;
    const DWORD  sh_link;
    const DWORD  sh_info;
    const QWORD  sh_addralign;
    const QWORD  sh_entsize;
    constexpr Section_Header (const DWORD  _sh_name,   const DWORD  _sh_type,      const QWORD  _sh_flags,     const QWORD  _sh_addr,
                              const QWORD  _sh_offset, const QWORD  _sh_size,      const DWORD  _sh_link,
                              const DWORD  _sh_info,   const QWORD  _sh_addralign, const QWORD  _sh_entsize) 
    :   sh_name   (_sh_name),   sh_type      (_sh_type),      sh_flags   (_sh_flags),  sh_addr (_sh_addr),
        sh_offset (_sh_offset), sh_size      (_sh_size),      sh_link    (_sh_link), 
        sh_info   (_sh_info),   sh_addralign (_sh_addralign), sh_entsize (_sh_entsize) {}

};
#pragma pack (pop)


constexpr Program_Header PH_TEXT = {
    1,                               // p_type
    PF_X + PF_R,                     // p_flags            
    SizeOdDataSegm,                  // p_offset
    0x400000 + SizeOdDataSegm,       // p_vaddr = 0x400000 + TEXT_p_offset
    0x400000 + SizeOdDataSegm,       // p_paddr = TEXT_p_vaddr
    64,                              // p_filesz
    64,                              // p_memsz
    0x200000                         // p_align
};

constexpr Program_Header PH_DATA = {
    1,                               // p_type
    PF_W + PF_R,                     // p_flags            
    0,                               // p_offset
    0x600000,                        // p_vaddr = 0x600000 + DATA_p_offset
    0x600000,                        // p_paddr = DATA_p_vaddr
    SizeOdDataSegm,                  // p_filesz
    SizeOdDataSegm,                  // p_memsz
    0x200000                         // p_align
};

constexpr Section_Header SH_TEXT = {
    0,                                // sh_name
    1,                                // sh_type
    6,                                // sh_flags
    0x400170,                         // sh_addr
    0x170,                            // sh_offset
    64,                               // sh_size
    0,                                // sh_link
    0,                                // sh_info
    0x10,                             // sh_addralign
    0                                 // sh_entsize
};

constexpr Section_Header SH_DATA = {
    0,                                // sh_name
    1,                                // sh_type
    0x03,                                // sh_flags
    0x600130,                         // sh_addr
    0x130,                            // sh_offset
    SizeOdDataSegm,                               // sh_size
    0,                                // sh_link
    0,                                // sh_info
    0x04,                             // sh_addralign
    0                                 // sh_entsize
};


class ELF {
    unsigned char* buf;
    unsigned char* bf_ptr;
    unsigned int bf_size;
    std::unique_ptr <ELF_Header> header;
    std::unique_ptr <Program_Header> ph_text;
    std::unique_ptr <Program_Header> ph_data;
    std::unique_ptr <Section_Header> sh_text;
    std::unique_ptr <Section_Header> sh_data;
    Code code;
public:
    ELF (const Code& _code);
    ~ELF ();
    void load_to_file (const char* path);
    
};

unsigned int set_zeros (unsigned char* bf_ptr, unsigned int number);

const unsigned char r_code[] = {
0x90,             	            // nop
0x90,             	            // nop
0x90,             	            // nop
0x55,             	            // push   %rbp
0x48, 0x89, 0xe5,             	    // mov    %rsp,%rbp
0x90,             	            // nop
0x90,            	            // nop
0x90,            	            // nop
0x48, 0x8b, 0x5d, 0xf8,          	// mov    -0x8(%rbp),%rbx
0x48, 0x8b, 0x5d, 0xf0,          	// mov    -0x10(%rbp),%rbx
0x48, 0x8b, 0x5d, 0xe8,          	// mov    -0x18(%rbp),%rbx
0x48, 0x8b, 0x5d, 0xe0,          	// mov    -0x20(%rbp),%rbx
0x90,            	// nop
0x48, 0x8b, 0x4d, 0xf8,          	// mov    -0x8(%rbp),%rcx
0x48, 0x8b, 0x4d, 0xf0,          	// mov    -0x10(%rbp),%rcx
0x48, 0x8b, 0x4d, 0xe8,          	// mov    -0x18(%rbp),%rcx
0x48, 0x8b, 0x4d, 0xe0,          	// mov    -0x20(%rbp),%rcx
0xb8, 0x01, 0x00, 0x00, 0x00,       	// mov    $0x1,%eax
0xbb, 0x00, 0x00, 0x00, 0x00,       	// mov    $0x0,%ebx
0xcd, 0x80, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90}; // 


#endif //ELF_H

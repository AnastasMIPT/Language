#ifndef ELF_H
#define ELF_H

#include <cstdio>
#include "Commands.h"

template <typename Type>
unsigned int set_elem (char* buf_ptr, const Type* elem);

typedef unsigned char      BYTE;
typedef unsigned short int WORD;
typedef unsigned int       DWORD;
typedef unsigned long long QWORD;

constexpr DWORD PF_X = 1;
constexpr DWORD PF_W = 2;
constexpr DWORD PF_R = 4;


constexpr unsigned long long SizeOdDataSegm = 64;



constexpr DWORD  TEXT_p_flags  = PF_X + PF_R;
constexpr QWORD  TEXT_p_offset = SizeOdDataSegm;            //Offset segment from 
constexpr QWORD  TEXT_p_vaddr  = 0x400000 + TEXT_p_offset;
constexpr QWORD  TEXT_p_paddr  = TEXT_p_vaddr;
constexpr QWORD  TEXT_p_filesz = 64;         //SizeOfSegment in file     ????
constexpr QWORD  TEXT_p_memsz  = 64;         //SizeOfSegment in memory   ????
constexpr QWORD  TEXT_p_align  = 0x200000;


constexpr DWORD  DATA_p_flags  = PF_W + PF_R;
constexpr QWORD  DATA_p_offset = 0;            //Offset segment from start of file
constexpr QWORD  DATA_p_vaddr  = 0x600000 + DATA_p_offset;
constexpr QWORD  DATA_p_paddr  = DATA_p_vaddr;
constexpr QWORD  DATA_p_filesz = SizeOdDataSegm;
constexpr QWORD  DATA_p_memsz  = SizeOdDataSegm;
constexpr QWORD  DATA_p_align  = 0x200000;


constexpr DWORD  TEXT_sh_type      = 1;    
constexpr QWORD  TEXT_sh_flags     = 6;   
constexpr QWORD  TEXT_sh_addr      = 0x400170;
constexpr QWORD  TEXT_sh_offset    = 0x170;
constexpr QWORD  TEXT_sh_size      = 64; ///////
constexpr DWORD  TEXT_sh_link      = 0;
constexpr DWORD  TEXT_sh_info      = 0;
constexpr QWORD  TEXT_sh_addralign = 0x10;
constexpr QWORD  TEXT_sh_entsize   = 0;


constexpr DWORD  DATA_sh_type      = 1;
constexpr QWORD  DATA_sh_flags     = 0x03;
constexpr QWORD  DATA_sh_addr      = 0x600130;
constexpr QWORD  DATA_sh_offset    = 0x130;
constexpr QWORD  DATA_sh_size      = SizeOdDataSegm;   // Size of data
constexpr DWORD  DATA_sh_link      = 0;
constexpr DWORD  DATA_sh_info      = 0;
constexpr QWORD  DATA_sh_addralign = 0x04;
constexpr QWORD  DATA_sh_entsize   = 0;
    



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
    const DWORD  p_type = 1;     // LOAD
    const DWORD  p_flags;        // segment flags
    const QWORD  p_offset; 
    const QWORD  p_vaddr;
    const QWORD  p_paddr;
    const QWORD  p_filesz;
    const QWORD  p_memsz;
    const QWORD  p_align;
    constexpr Program_Header (const DWORD  _p_flags, const QWORD  _p_offset, const QWORD  _p_vaddr,
                              const QWORD  _p_paddr, const QWORD  _p_filesz, const QWORD  _p_memsz,
                              const QWORD  _p_align) 
    :   p_flags (_p_flags), p_offset (_p_offset), p_vaddr (_p_vaddr),
        p_paddr (_p_paddr), p_filesz (_p_filesz), p_memsz (_p_memsz), p_align (_p_align) {}

};
#pragma pack (pop)

#pragma pack (push, 1)
struct Section_Header {
    const DWORD  sh_name = 0;   
    const DWORD  sh_type;    
    const QWORD  sh_flags;   
    const QWORD  sh_addr;
    const QWORD  sh_offset;
    const QWORD  sh_size;
    const DWORD  sh_link;
    const DWORD  sh_info;
    const QWORD  sh_addralign;
    const QWORD  sh_entsize;
    constexpr Section_Header (const DWORD  _sh_type,   const QWORD  _sh_flags,     const QWORD  _sh_addr,
                              const QWORD  _sh_offset, const QWORD  _sh_size,      const DWORD  _sh_link,
                              const DWORD  _sh_info,   const QWORD  _sh_addralign, const QWORD  _sh_entsize) 
    :   sh_type (_sh_type),     sh_flags (_sh_flags),         sh_addr (_sh_addr),
        sh_offset (_sh_offset), sh_size (_sh_size),           sh_link (_sh_link), 
        sh_info (_sh_info),     sh_addralign (_sh_addralign), sh_entsize (_sh_entsize) {}

};
#pragma pack (pop)

class ELF {
    char* buf;
    char* bf_ptr;
    unsigned int bf_size;
    ELF_Header* header;
    Program_Header* ph_text;
    Program_Header* ph_data;
    Section_Header* sh_text;
    Section_Header* sh_data;
public:
    ELF (unsigned int _bf_size);
    ~ELF ();
    void load_to_file (const char* path);
    unsigned int set_zeros (char* bf_ptr, int number);
};


class Code {
    char* byte_code;
    char* code_ptr;
    unsigned int size;
public:
    unsigned int get_size () const;
    char* get_code_buf () const;
    void add_command  (const Command& command);
};



char code[] = {0x90,             	            // nop
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

#include <cstdio>

template <typename Type>
unsigned int set_elem (char* buf_ptr, const Type* elem);

typedef unsigned char      BYTE;
typedef unsigned short int WORD;
typedef unsigned int       DWORD;
typedef unsigned long long QWORD;

constexpr DWORD PF_X = 1;
constexpr DWORD PF_W = 2;
constexpr DWORD PF_R = 4;



constexpr DWORD  TEXT_p_flags  = PF_X + PF_R;
constexpr QWORD  TEXT_p_offset = 0;            //Offset segment from 
constexpr QWORD  TEXT_p_vaddr  = 0x400000;
constexpr QWORD  TEXT_p_paddr  = 0x400000;
constexpr QWORD  TEXT_p_filesz = 0xd6;         //SizeOfSegment in file
constexpr QWORD  TEXT_p_memsz  = 0xd6;         //SizeOfSegment in memory
constexpr QWORD  TEXT_p_align  = 0x200000;


constexpr DWORD  DATA_p_flags  = PF_W + PF_R;
constexpr QWORD  DATA_p_offset = 0xd8;            //Offset segment from start of file
constexpr QWORD  DATA_p_vaddr  = 0x6000d8;
constexpr QWORD  DATA_p_paddr  = 0x6000d8;
constexpr QWORD  DATA_p_filesz = 10;
constexpr QWORD  DATA_p_memsz  = 10;
constexpr QWORD  DATA_p_align  = 0x200000;


constexpr DWORD  TEXT_sh_type      = 1;    
constexpr QWORD  TEXT_sh_flags     = 6;   
constexpr QWORD  TEXT_sh_addr      = 0x4000b0;
constexpr QWORD  TEXT_sh_offset    = 0xb0;
constexpr QWORD  TEXT_sh_size      = 0x37; ///////
constexpr DWORD  TEXT_sh_link      = 0;
constexpr DWORD  TEXT_sh_info      = 0;
constexpr QWORD  TEXT_sh_addralign = 0x10;
constexpr QWORD  TEXT_sh_entsize   = 0;


constexpr DWORD  DATA_sh_type      = 1;
constexpr QWORD  DATA_sh_flags     = 0x03;
constexpr QWORD  DATA_sh_addr      = 0x6000e8;
constexpr QWORD  DATA_sh_offset    = 0xe8;
constexpr QWORD  DATA_sh_size      = 0x0a;   ///
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
    const QWORD  e_entry      = 0x000000000004000b;  // virtual point of entry
    const QWORD  e_phoff      = 0x40;                // Program header offset
    const QWORD  e_shoff      = 0x0110;              // Section header offset
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

struct code {
    char* byte_code;

};


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
};
#ifndef ELF_CPP
#define ELF_CPP


#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "ELF.h"
#include "Commands.h"
#include"Func_b.h"

template <typename Type>
unsigned int set_elem (char* buf_ptr, const Type* elem) {
    unsigned int size = sizeof (Type);
    memcpy (buf_ptr, elem, size);
    return size;
}



ELF::~ELF () {
    free (buf);
    delete header;
    delete ph_text;
    delete ph_data;
    delete sh_text;
    delete sh_data;
}

unsigned int set_zeros (char* bf_ptr, unsigned int number) {
    memchr (bf_ptr, 0, number);
    return number;
}


ELF::ELF (unsigned int _bf_size, Code* _code) : bf_size (_bf_size), code (_code) {
    buf    = reinterpret_cast<char*> (calloc (bf_size, sizeof (char)));
    bf_ptr = buf;
    printf ("Hello**\n");
    
    header =  new ELF_Header;
    bf_ptr += set_elem (bf_ptr, header);

    ph_text = new Program_Header (TEXT_p_flags,  TEXT_p_offset, TEXT_p_vaddr, TEXT_p_paddr,
                                  TEXT_p_filesz, TEXT_p_memsz,  TEXT_p_align);
    bf_ptr += set_elem (bf_ptr, ph_text);

    ph_data = new Program_Header (DATA_p_flags,  DATA_p_offset, DATA_p_vaddr, DATA_p_paddr,
                                  DATA_p_filesz, DATA_p_memsz,  DATA_p_align);
    bf_ptr += set_elem (bf_ptr, ph_data);

    sh_text = new Section_Header (TEXT_sh_type, TEXT_sh_flags, TEXT_sh_addr,      TEXT_sh_offset, TEXT_sh_size,
                                  TEXT_sh_link, TEXT_sh_info,  TEXT_sh_addralign, TEXT_sh_entsize);
    bf_ptr += set_elem (bf_ptr, sh_text);

    sh_data = new Section_Header (DATA_sh_type, DATA_sh_flags, DATA_sh_addr,      DATA_sh_offset, DATA_sh_size,
                                  DATA_sh_link, DATA_sh_info,  DATA_sh_addralign, DATA_sh_entsize);
    bf_ptr += set_elem  (bf_ptr, sh_data);
    
    bf_ptr += set_zeros (bf_ptr, SizeOdDataSegm);

    memcpy (bf_ptr, r_code, 64);
    bf_ptr += 64;
    memcpy (bf_ptr, itoa_b, SizeItoa);
    bf_ptr += SizeItoa;
    memcpy (bf_ptr, output_b, SizeOutput);
    bf_ptr += SizeOutput;
    
    bf_ptr += set_zeros (bf_ptr, 2);
}

void ELF::load_to_file (const char * path) {
     FILE* f_out = fopen (path, "wb");
    
    if (!f_out) {
        const char * command =  strcat (const_cast<char*> ("touch "), path);
        system (command);
        f_out = fopen (path, "wb");
    }
    
    fwrite (buf, sizeof (char), bf_size, f_out);
    fclose (f_out);
}


unsigned int Code::get_size () const {
    return size;
}

char* Code::get_code_buf () const {
    return buf;
}

void Code::add_command  (const Command& command) {
    command.write_to_buf (buf_ptr);
    buf_ptr += command.get_byte_num ();
    size += command.get_byte_num ();
}

void Code::write_from_buf (unsigned char* _buf, unsigned int num) {
    assert (_buf);
    memcpy (buf_ptr, _buf, num);
    printf ("hello33\n");
    buf_ptr += num;
    size += num;
}

Code::Code (unsigned int buf_size) {
    buf = reinterpret_cast <char*> (calloc (buf_size, sizeof (char)));
}

Code::~Code () {
    free (buf);
}

#endif //ELF_CPP
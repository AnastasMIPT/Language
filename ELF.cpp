#ifndef ELF_CPP
#define ELF_CPP

//#define DEBUG

#ifdef DEBUG
    #define DEB_INFO printf ("DEBUG_INFO:  Called from FILE: %s from FUNCTION: %s   LINE: %d\n", __FILE__, __func__, __LINE__);
#else 
    #define DEB_INFO ;
#endif


#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "ELF.h"
#include "Func_b.h"


template <typename Type>
unsigned int set_elem (unsigned char* buf_ptr, const Type* elem) {
    unsigned int size = sizeof (Type);
    memcpy (buf_ptr, elem, size);
    return size;
}



ELF::~ELF () {
    assert (buf);
    DEB_INFO
    free (buf);
    DEB_INFO
}

unsigned int set_zeros (unsigned char* bf_ptr, unsigned int number) {
    assert (bf_ptr);

    memchr (bf_ptr, '\0', number);
    return number;
}


ELF::ELF (const Code& _code) : bf_size (_code.get_size () + SizeItoa + SizeOutput + SizeOfELF_header), code (_code) {
    unsigned int num_of_add_zeros = 16 - (bf_size % 16);
    bf_size += num_of_add_zeros;

    buf    = reinterpret_cast<unsigned char*> (calloc (bf_size, sizeof (unsigned char)));
    bf_ptr = buf;

    assert (buf);

    //printf ("Hello**\n");
    
    header =  std::make_unique <ELF_Header> ();
    bf_ptr += set_elem (bf_ptr, header.get ());

    ph_text = std::make_unique <Program_Header> (TEXT_p_flags,  TEXT_p_offset, TEXT_p_vaddr, TEXT_p_paddr,
                                  TEXT_p_filesz, TEXT_p_memsz,  TEXT_p_align);
    bf_ptr += set_elem (bf_ptr, ph_text.get ());

    ph_data = std::make_unique <Program_Header> (DATA_p_flags,  DATA_p_offset, DATA_p_vaddr, DATA_p_paddr,
                                  DATA_p_filesz, DATA_p_memsz,  DATA_p_align);
    bf_ptr += set_elem (bf_ptr, ph_data.get ());

    sh_text = std::make_unique <Section_Header> (TEXT_sh_type, TEXT_sh_flags, TEXT_sh_addr,      TEXT_sh_offset, TEXT_sh_size,
                                  TEXT_sh_link, TEXT_sh_info,  TEXT_sh_addralign, TEXT_sh_entsize);
    bf_ptr += set_elem (bf_ptr, sh_text.get ());

    sh_data = std::make_unique <Section_Header> (DATA_sh_type, DATA_sh_flags, DATA_sh_addr,      DATA_sh_offset, DATA_sh_size,
                                  DATA_sh_link, DATA_sh_info,  DATA_sh_addralign, DATA_sh_entsize);
    bf_ptr += set_elem  (bf_ptr, sh_data.get ());
    
    // printf ("pointer before %p\n", bf_ptr);
    bf_ptr += set_zeros (bf_ptr, SizeOdDataSegm);
    // printf ("data %d\n", *reinterpret_cast<int*> (bf_ptr - 4));
    // printf ("pointer after %p\n", bf_ptr);

    memcpy (bf_ptr, _code.get_code_buf () , _code.get_size ());
    bf_ptr += _code.get_size ();
    memcpy (bf_ptr, itoa_b, SizeItoa);
    bf_ptr += SizeItoa;
    memcpy (bf_ptr, output_b, SizeOutput);
    bf_ptr += SizeOutput;
    
    bf_ptr += set_zeros (bf_ptr, num_of_add_zeros);
}

void ELF::load_to_file (const char * path) {
    DEB_INFO
    FILE* f_out = fopen (path, "wb");
    
    if (!f_out) {
        DEB_INFO
        const char * command =  strcat (const_cast<char*> ("touch "), path);
        system (command);
        f_out = fopen (path, "wb");
    }
    DEB_INFO
    fwrite (buf, sizeof (char), bf_size, f_out);
    DEB_INFO
    fclose (f_out);
}

#endif //ELF_CPP
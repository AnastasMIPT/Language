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


ELF::ELF (const Code& _code) : bf_size (_code.get_size () /* + SizeItoa + SizeOutput*/ +  SizeOfELF_header), code (_code) {
    
    unsigned int num_of_add_zeros = 16 - (bf_size % 16);
    bf_size += num_of_add_zeros;
    
    buf    = reinterpret_cast <unsigned char*> (calloc (bf_size, sizeof (unsigned char)));
    bf_ptr = buf;

    assert (buf);

    header =  std::make_unique <ELF_Header> ();
    bf_ptr += set_elem (bf_ptr, header.get ());

    ph_text = std::make_unique <Program_Header> (PH_TEXT);
    bf_ptr += set_elem (bf_ptr, ph_text.get ());

    ph_data = std::make_unique <Program_Header> (PH_DATA);
    bf_ptr += set_elem (bf_ptr, ph_data.get ());

    sh_text = std::make_unique <Section_Header> (SH_TEXT);
    bf_ptr += set_elem (bf_ptr, sh_text.get ());

    sh_data = std::make_unique <Section_Header> (SH_DATA);
    bf_ptr += set_elem  (bf_ptr, sh_data.get ());
    

    bf_ptr += set_zeros (bf_ptr, SizeOdDataSegm);
    
    memcpy (bf_ptr, _code.get_code_buf () , _code.get_size ());
    bf_ptr += _code.get_size ();
    
    /*memcpy (bf_ptr, itoa_b, SizeItoa);
    bf_ptr += SizeItoa;
    memcpy (bf_ptr, output_b, SizeOutput);
    bf_ptr += SizeOutput;*/
    
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
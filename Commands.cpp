#ifndef COMMANDS_CPP
#define COMMANDS_CPP

//#define DEBUG

#ifdef DEBUG
    #define DEB_INFO printf ("DEBUG_INFO:  Called from FILE: %s from FUNCTION: %s   LINE: %d\n", __FILE__, __func__, __LINE__);
#else 
    #define DEB_INFO ;
#endif


#include "Commands.h"
#include "ELF.h"
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <sys/stat.h>


unsigned int Code::get_size () const {
    return size;
}

unsigned char* Code::get_code_buf () const {
    return buf;
}

void Code::add_command  (const Command& command) {
    command.write_to_buf (buf_ptr);
    buf_ptr += command.get_byte_num ();
    size += command.get_byte_num ();
}

void Code::write_from_buf (unsigned char* _buf, unsigned int num) {
    assert (_buf);
    //assert (buf_ptr);
   
    DEB_INFO
    memcpy (buf_ptr, _buf, num);
    DEB_INFO
    buf_ptr += num;
    size += num;
}

Code::Code (unsigned int buf_size) : size (0) {
    buf = reinterpret_cast <unsigned char*> (calloc (buf_size, sizeof (char)));
    buf_ptr = buf;
}

Code::Code (const unsigned char* _buf, const unsigned int buf_size) : size (buf_size) {
    DEB_INFO
    buf = reinterpret_cast <unsigned char*> (calloc (buf_size, sizeof (char)));
    memcpy (buf, _buf, buf_size);
    buf_ptr = buf + buf_size;
}
    
Code::Code (const Code& other) : size (other.get_size ()) {
    buf = reinterpret_cast <unsigned char*> (calloc (size, sizeof (char)));
    memcpy (buf, other.get_code_buf (), size);
    buf_ptr = buf + size;
}


Code::~Code () {
    assert (buf);
    DEB_INFO
    free (buf);
    DEB_INFO
}





unsigned int Call::get_byte_num () const {
    return byte_num;
}

void Call::write_to_buf (unsigned char* buf) const {
    assert (buf);

    *buf = 0xe8;
    *reinterpret_cast<QWORD*> (buf + 1) = offset;
}





#endif //COMMANDS_CPP
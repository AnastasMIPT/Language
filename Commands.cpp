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



unsigned int RM_REG_by_registers (unsigned int to, unsigned int from) {
    printf ("hhhh %u\n", 192U + to + (from << 3) + 0U);
    return to + (from << 3);
}



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

void Mov64_RR::write_to_buf (unsigned char* buf) const {
        set_elems (buf,  REX (1) , OpCode (0x89) , ModRM (0b11, RM_REG_by_registers (to, from)));
}

unsigned int Mov64_RR::get_byte_num () const {
    return byte_num;
}

Mov64_RM::Mov64_RM (unsigned int _to, int _from_offset)
: to (_to), from_offset (_from_offset) {
    setbuf (stdout, NULL);
    byte_num = ( -128 <= from_offset && from_offset < 128 ? 4 : 7);
    DEB_INFO
    printf ("byte_num constr = %u\n", byte_num);
}

void Mov64_RM::write_to_buf (unsigned char* buf) const {
        if (byte_num == 4) {
            DEB_INFO
            unsigned char displacment = from_offset;
            set_elems (buf,  REX (1) , OpCode (0x8b) , ModRM (0b01, to << 3, 0b101), displacment);
        } else {
            DEB_INFO
            printf ("byte_num = %u\n", byte_num);
            set_elems (buf,  REX (1) , OpCode (0x8b) , ModRM (0b10, to << 3, 0b101), from_offset);
        }
}

unsigned int Mov64_RM::get_byte_num () const {
    return byte_num;
}




Mov64_MR::Mov64_MR (int _from_offset, unsigned int _to)
: to (_to), from_offset (_from_offset) {
    //setbuf (stdout, NULL);
    byte_num = ( -128 <= from_offset && from_offset < 128 ? 4 : 7);
    //DEB_INFO
    //printf ("byte_num constr = %u\n", byte_num);
}

void Mov64_MR::write_to_buf (unsigned char* buf) const {
        if (byte_num == 4) {
            //DEB_INFO
            unsigned char displacment = from_offset;
            set_elems (buf,  REX (1) , OpCode (0x89) , ModRM (0b01, to << 3, 0b101), displacment);
        } else {
            //DEB_INFO
            //printf ("byte_num = %u\n", byte_num);
            set_elems (buf,  REX (1) , OpCode (0x89) , ModRM (0b10, to << 3, 0b101), from_offset);
        }
}

unsigned int Mov64_MR::get_byte_num () const {
    return byte_num;
}





Mov64_MImm::Mov64_MImm (int _from_offset, int _imm)
: from_offset (_from_offset), imm (_imm) {
    //setbuf (stdout, NULL);
    byte_num = ( -128 <= from_offset && from_offset < 128 ? 8 : 11);
    //DEB_INFO
    //printf ("byte_num constr = %u\n", byte_num);
}

void Mov64_MImm::write_to_buf (unsigned char* buf) const {
        if (byte_num == 8) {
            //DEB_INFO
            unsigned char displacment = from_offset;
            set_elems (buf,  REX (1) , OpCode (0xc7) , ModRM (0b01, 0, 0b101), displacment, imm);
        } else {
            //DEB_INFO
            //printf ("byte_num = %u\n", byte_num);
            set_elems (buf,  REX (1) , OpCode (0xc7) , ModRM (0b10, 0, 0b101), from_offset, imm);
        }
}

unsigned int Mov64_MImm::get_byte_num () const {
    return byte_num;
}




Mov64_RImm::Mov64_RImm (unsigned int _to, int _imm)
: to (_to), imm (_imm) {
    //setbuf (stdout, NULL);
    byte_num = ( imm < 0 ? 7 : 5);
    //DEB_INFO
    //printf ("byte_num constr = %u\n", byte_num);
}

void Mov64_RImm::write_to_buf (unsigned char* buf) const {
        if (byte_num == 7) {
            set_elems (buf,  REX (1) , OpCode (0xc7) , ModRM (0b11, 0, to), imm);
        } else {
            set_elems (buf,  OpCode (0xb8 + to) , imm);
        }
}

unsigned int Mov64_RImm::get_byte_num () const {
    return byte_num;
}

#endif //COMMANDS_CPP
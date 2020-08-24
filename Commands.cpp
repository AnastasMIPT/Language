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
#include "Func_b.h"
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

unsigned char* Code::get_code_buf_ptr () const {
    return buf_ptr;
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


unsigned int Cmd::Call::get_byte_num () const {
    return byte_num;
}

void Cmd::Call::write_to_buf (unsigned char* buf) const {
    assert (buf);

    *buf = 0xe8;
    if (label_requests) {
        (*label_requests).emplase_back (func_name, buf + 1); // do request for label
    }
    *reinterpret_cast<QWORD*> (buf + 1) = offset;
}



void Cmd::Je::write_to_buf (unsigned char* buf) const {
    assert (buf);

    set_elems (buf, OpCode (0x0f), OpCode (0x84));
    if (label_requests) {
        (*label_requests).emplase_back (cond_name, buf + 2); // do request for label
    }
    *reinterpret_cast<QWORD*> (buf + 2) = offset;
}

unsigned int Cmd::Je::get_byte_num () const {
    return byte_num;
}


void Cmd::Jne::write_to_buf (unsigned char* buf) const {
    assert (buf);

    set_elems (buf, OpCode (0x0f), OpCode (0x85));
    if (label_requests) {
        (*label_requests).emplase_back (cond_name, buf + 2); // do request for label
    }
    *reinterpret_cast<QWORD*> (buf + 2) = offset;
}

unsigned int Cmd::Jne::get_byte_num () const {
    return byte_num;
}


void Cmd::Jg::write_to_buf (unsigned char* buf) const {
    assert (buf);

    set_elems (buf, OpCode (0x0f), OpCode (0x8f));
    if (label_requests) {
        (*label_requests).emplase_back (cond_name, buf + 2); // do request for label
    }
    *reinterpret_cast<QWORD*> (buf + 2) = offset;
}

unsigned int Cmd::Jg::get_byte_num () const {
    return byte_num;
}

void Cmd::Mov64_RR::write_to_buf (unsigned char* buf) const {
        set_elems (buf,  REX (1) , OpCode (0x89) , ModRM (0b11, RM_REG_by_registers (to, from)));
}

unsigned int Cmd::Mov64_RR::get_byte_num () const {
    return byte_num;
}




void Cmd::Mov64_RAddr::write_to_buf (unsigned char* buf) const {
        set_elems (buf,  REX (1) , OpCode (0x8b) , ModRM (0b00, to << 3, 0b100), SIB (0b00, 0b100, 0b101), addr);
}

unsigned int Cmd::Mov64_RAddr::get_byte_num () const {
    return byte_num;
}


void Cmd::Mov64_AddrR::write_to_buf (unsigned char* buf) const {
        set_elems (buf,  REX (1) , OpCode (0x89) , ModRM (0b00, from << 3, 0b100), SIB (0b00, 0b100, 0b101), addr);
}

unsigned int Cmd::Mov64_AddrR::get_byte_num () const {
    return byte_num;
}




Cmd::Mov64_RM::Mov64_RM (unsigned int _to, int _mem_offset)
: to (_to), mem_offset (_mem_offset) {
    setbuf (stdout, NULL);
    byte_num = ( -128 <= mem_offset && mem_offset < 128 ? 4 : 7);
    DEB_INFO
    printf ("byte_num constr = %u\n", byte_num);
}

void Cmd::Mov64_RM::write_to_buf (unsigned char* buf) const {
        if (byte_num == 4) {
            DEB_INFO
            unsigned char displacment = mem_offset;
            set_elems (buf,  REX (1) , OpCode (0x8b) , ModRM (0b01, to << 3, 0b101), displacment);
        } else {
            DEB_INFO
            printf ("byte_num = %u\n", byte_num);
            set_elems (buf,  REX (1) , OpCode (0x8b) , ModRM (0b10, to << 3, 0b101), mem_offset);
        }
}

unsigned int Cmd::Mov64_RM::get_byte_num () const {
    return byte_num;
}




Cmd::Mov64_MR::Mov64_MR (int _mem_offset, unsigned int _to)
: to (_to), mem_offset (_mem_offset) {
    //setbuf (stdout, NULL);
    byte_num = ( -128 <= mem_offset && mem_offset < 128 ? 4 : 7);
    //DEB_INFO
    //printf ("byte_num constr = %u\n", byte_num);
}

void Cmd::Mov64_MR::write_to_buf (unsigned char* buf) const {
        if (byte_num == 4) {
            //DEB_INFO
            unsigned char displacment = mem_offset;
            set_elems (buf,  REX (1) , OpCode (0x89) , ModRM (0b01, to << 3, 0b101), displacment);
        } else {
            //DEB_INFO
            //printf ("byte_num = %u\n", byte_num);
            set_elems (buf,  REX (1) , OpCode (0x89) , ModRM (0b10, to << 3, 0b101), mem_offset);
        }
}

unsigned int Cmd::Mov64_MR::get_byte_num () const {
    return byte_num;
}





Cmd::Mov64_MImm::Mov64_MImm (int _mem_offset, int _imm)
: mem_offset (_mem_offset), imm (_imm) {
    //setbuf (stdout, NULL);
    byte_num = ( -128 <= mem_offset && mem_offset < 128 ? 8 : 11);
    //DEB_INFO
    //printf ("byte_num constr = %u\n", byte_num);
}

void Cmd::Mov64_MImm::write_to_buf (unsigned char* buf) const {
        if (byte_num == 8) {
            //DEB_INFO
            unsigned char displacment = mem_offset;
            set_elems (buf,  REX (1) , OpCode (0xc7) , ModRM (0b01, 0, 0b101), displacment, imm);
        } else {
            //DEB_INFO
            //printf ("byte_num = %u\n", byte_num);
            set_elems (buf,  REX (1) , OpCode (0xc7) , ModRM (0b10, 0, 0b101), mem_offset, imm);
        }
}

unsigned int Cmd::Mov64_MImm::get_byte_num () const {
    return byte_num;
}




Cmd::Mov64_RImm::Mov64_RImm (unsigned int _to, int _imm)
: to (_to), imm (_imm) {
    if (to < 8) {
        byte_num = ( imm < 0 ? 7 : 5);
    } else {
        byte_num = ( imm < 0 ? 7 : 6);
    }
}

void Cmd::Mov64_RImm::write_to_buf (unsigned char* buf) const {
        if (byte_num == 7) {
            if (to < 8) {
                set_elems (buf,  REX (1) , OpCode (0xc7) , ModRM (0b11, 0, to), imm);
            } else {
                set_elems (buf,  REX (1, 0, 0, 1) , OpCode (0xc7) , ModRM (0b11, 0, to - 8), imm);
            }
        } else if (byte_num == 5){
            set_elems (buf,  OpCode (0xb8 + to) , imm);
        } else {
            set_elems (buf,  REX (0, 0, 0, 1), OpCode (0xb8 + to - 8) , imm);
        }
}

unsigned int Cmd::Mov64_RImm::get_byte_num () const {
    return byte_num;
}




Cmd::PushM::PushM (int _mem_offset)
: mem_offset (_mem_offset) {
    byte_num = (-128 <= mem_offset && mem_offset < 128 ? 3 : 6);
}

void Cmd::PushM::write_to_buf (unsigned char* buf) const {
        if (byte_num == 3) {
            set_elems (buf,  OpCode (0xff) , ModRM (0b01, 0b110 << 3, 0b101), static_cast<unsigned char> (mem_offset));
        } else {
            set_elems (buf,  OpCode (0xff) , ModRM (0b10, 0b110 << 3, 0b101), mem_offset);
        }
}

unsigned int Cmd::PushM::get_byte_num () const {
    return byte_num;
}



Cmd::PushImm::PushImm (int _imm)
: imm (_imm) {
    byte_num = (-128 <= imm && imm < 128 ? 2 : 5);
}

void Cmd::PushImm::write_to_buf (unsigned char* buf) const {
        if (byte_num == 2) {
            set_elems (buf,  OpCode (0x6a), static_cast<unsigned char> (imm));
        } else {
            set_elems (buf,  OpCode (0x68) , imm);
        }
}

unsigned int Cmd::PushImm::get_byte_num () const {
    return byte_num;
}



Cmd::PushR::PushR (unsigned int _reg)
: reg (_reg), byte_num (1) {}

void Cmd::PushR::write_to_buf (unsigned char* buf) const {
    set_elems (buf,  OpCode (0x50+reg));
}

unsigned int Cmd::PushR::get_byte_num () const {
    return byte_num;
}




Cmd::PopR::PopR (unsigned int _reg)
: reg (_reg), byte_num (1) {}

void Cmd::PopR::write_to_buf (unsigned char* buf) const {
    set_elems (buf,  OpCode (0x58+reg));
}

unsigned int Cmd::PopR::get_byte_num () const {
    return byte_num;
}



void Cmd::Add64_RR::write_to_buf (unsigned char* buf) const {
        set_elems (buf,  REX (1) , OpCode (0x01) , ModRM (0b11, RM_REG_by_registers (to, from)));
}

unsigned int Cmd::Add64_RR::get_byte_num () const {
    return byte_num;
}




Cmd::Add64_RM::Add64_RM (unsigned int _to, int _mem_offset)
: to (_to), mem_offset (_mem_offset) {
    byte_num = ( -128 <= mem_offset && mem_offset < 128 ? 4 : 7);
}

void Cmd::Add64_RM::write_to_buf (unsigned char* buf) const {
        if (byte_num == 4) {
            unsigned char displacment = mem_offset;
            set_elems (buf,  REX (1) , OpCode (0x03) , ModRM (0b01, to << 3, 0b101), displacment);
        } else {
            set_elems (buf,  REX (1) , OpCode (0x03) , ModRM (0b10, to << 3, 0b101), mem_offset);
        }
}

unsigned int Cmd::Add64_RM::get_byte_num () const {
    return byte_num;
}



Cmd::Add64_RImm::Add64_RImm (unsigned int _to, int _imm)
: to (_to), imm (_imm) {
    if (to == REGS::RAX) {
        byte_num = ( -128 <= imm && imm < 128 ? 4 : 6);
    } else {
        byte_num = ( -128 <= imm && imm < 128 ? 4 : 7);
    }
}

void Cmd::Add64_RImm::write_to_buf (unsigned char* buf) const {
        if (byte_num == 4) {
            set_elems (buf,  REX (1) , OpCode (0x83) , ModRM (0b11, 0, to), static_cast<char> (imm));
        } else if (byte_num == 6) {
            set_elems (buf,  REX (1) , OpCode (0x05), imm);
        } else {
            set_elems (buf,  REX (1) , OpCode (0x81) , ModRM (0b11, 0, to), imm);
        }
}

unsigned int Cmd::Add64_RImm::get_byte_num () const {
    return byte_num;
}




Cmd::Sub64_RImm::Sub64_RImm (unsigned int _to, int _imm)
: to (_to), imm (_imm) {
    if (to == REGS::RAX) {
        byte_num = ( -128 <= imm && imm < 128 ? 4 : 6);
    } else {
        byte_num = ( -128 <= imm && imm < 128 ? 4 : 7);
    }
}

void Cmd::Sub64_RImm::write_to_buf (unsigned char* buf) const {
        if (byte_num == 4) {
            set_elems (buf,  REX (1) , OpCode (0x83) , ModRM (0b11, 0b101 << 3, to), static_cast<char> (imm));
        } else if (byte_num == 6) {
            set_elems (buf,  REX (1) , OpCode (0x2d), imm);
        } else {
            set_elems (buf,  REX (1) , OpCode (0x81) , ModRM (0b11, 0b101 << 3, to), imm);
        }
}

unsigned int Cmd::Sub64_RImm::get_byte_num () const {
    return byte_num;
}




Cmd::Sub64_RM::Sub64_RM (unsigned int _to, int _mem_offset)
: to (_to), mem_offset (_mem_offset) {
    byte_num = ( -128 <= mem_offset && mem_offset < 128 ? 4 : 7);
}

void Cmd::Sub64_RM::write_to_buf (unsigned char* buf) const {
        if (byte_num == 4) {
            unsigned char displacment = mem_offset;
            set_elems (buf,  REX (1) , OpCode (0x2b) , ModRM (0b01, to << 3, 0b101), displacment);
        } else {
            set_elems (buf,  REX (1) , OpCode (0x2b) , ModRM (0b10, to << 3, 0b101), mem_offset);
        }
}

unsigned int Cmd::Sub64_RM::get_byte_num () const {
    return byte_num;
}




void Cmd::Sub64_RR::write_to_buf (unsigned char* buf) const {
        set_elems (buf,  REX (1) , OpCode (0x29) , ModRM (0b11, RM_REG_by_registers (to, from)));
}

unsigned int Cmd::Sub64_RR::get_byte_num () const {
    return byte_num;
}


Cmd::Imul64_RImm::Imul64_RImm (unsigned int _to, int _imm)
: to (_to), imm (_imm) {
    byte_num = ( -128 <= imm && imm < 128 ? 4 : 7);
}

void Cmd::Imul64_RImm::write_to_buf (unsigned char* buf) const {
        if (byte_num == 4) {
            set_elems (buf,  REX (1) , OpCode (0x6b) , ModRM (0b11, to << 3, to), static_cast<char> (imm));
        } else {
            set_elems (buf,  REX (1) , OpCode (0x69) , ModRM (0b11, to << 3, to), imm);
        }
}

unsigned int Cmd::Imul64_RImm::get_byte_num () const {
    return byte_num;
}




void Cmd::Imul64_RR::write_to_buf (unsigned char* buf) const {
        set_elems (buf,  REX (1) , OpCode (0x0f) , OpCode (0xaf), ModRM (0b11, to << 3, from));
}

unsigned int Cmd::Imul64_RR::get_byte_num () const {
    return byte_num;
}




Cmd::Idiv_R::Idiv_R (unsigned int _reg)
: reg (_reg), byte_num (3) {}

void Cmd::Idiv_R::write_to_buf (unsigned char* buf) const {
    if (reg < 8) {
        set_elems (buf,  REX (1), OpCode (0xf7),ModRM (0b11, 0b110 << 3, 0b1000 + reg));
    } else {
        set_elems (buf,  REX (1, 0, 0, 1), OpCode (0xf7),ModRM (0b11, 0b110 << 3, 0b1000 + reg - 8));
    }
}

unsigned int Cmd::Idiv_R::get_byte_num () const {
    return byte_num;
}



Cmd::Ret::Ret ()
: byte_num (1) {}

void Cmd::Ret::write_to_buf (unsigned char* buf) const {
    set_elems (buf,  OpCode (0xc3));
}

unsigned int Cmd::Ret::get_byte_num () const {
    return byte_num;
}



Cmd::Cqo::Cqo ()
: byte_num (2) {}

void Cmd::Cqo::write_to_buf (unsigned char* buf) const {
    set_elems (buf, REX (1), OpCode (0x99));
}

unsigned int Cmd::Cqo::get_byte_num () const {
    return byte_num;
}



Cmd::Itoa::Itoa ()
: byte_num (SizeItoa) {}

void Cmd::Itoa::write_to_buf (unsigned char* buf) const {
    set_elems (buf,  itoa_b);
}

unsigned int Cmd::Itoa::get_byte_num () const {
    return byte_num;
}

Cmd::Atoi::Atoi ()
: byte_num (SizeAtoi) {}

void Cmd::Atoi::write_to_buf (unsigned char* buf) const {
    set_elems (buf,  atoi_b);
}

unsigned int Cmd::Atoi::get_byte_num () const {
    return byte_num;
}



Cmd::GStart::GStart ()
: byte_num (SizeGStart) {}

void Cmd::GStart::write_to_buf (unsigned char* buf) const {
    set_elems (buf,  g_start_b);
}

unsigned int Cmd::GStart::get_byte_num () const {
    return byte_num;
}




Cmd::OutputRBX::OutputRBX (unsigned char* _addr_of_itoa)
: addr_of_itoa (_addr_of_itoa) ,byte_num (SizeOutput) {}

void Cmd::OutputRBX::write_to_buf (unsigned char* buf) const {
    set_elems (buf,  output_b);
    printf ("output second pointer %p\n", buf+6);
    printf ("??? %x\n", (addr_of_itoa - (buf + 6)));
    *reinterpret_cast<unsigned int*> (buf + 2) = static_cast<unsigned int> (addr_of_itoa - (buf + 6));  // displacement by itoa ()
}

unsigned int Cmd::OutputRBX::get_byte_num () const {
    return byte_num;
}



Cmd::InputRAX::InputRAX (unsigned char* _addr_of_atoi)
: addr_of_atoi (_addr_of_atoi) ,byte_num (SizeInput) {}

void Cmd::InputRAX::write_to_buf (unsigned char* buf) const {
    set_elems (buf,  input_b);
    printf ("input second pointer %p\n", buf+37);
    *reinterpret_cast<unsigned int*>(buf + 33) = static_cast<unsigned int> (addr_of_atoi - (buf + 37));  // displacement by atoi ()
}

unsigned int Cmd::InputRAX::get_byte_num () const {
    return byte_num;
}


Cmd::Sqrt::Sqrt () : byte_num (SizeSqrt) {}

void Cmd::Sqrt::write_to_buf (unsigned char* buf) const {
    set_elems (buf,  sqrt_b);
}

unsigned int Cmd::Sqrt::get_byte_num () const {
    return byte_num;
}





void Cmd::Cmp_RR::write_to_buf (unsigned char* buf) const {
        set_elems (buf,  REX (1) , OpCode (0x39) , ModRM (0b11, RM_REG_by_registers (to, from)));
}

unsigned int Cmd::Cmp_RR::get_byte_num () const {
    return byte_num;
}



#endif //COMMANDS_CPP
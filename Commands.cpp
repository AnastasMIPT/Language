#ifndef COMMANDS_CPP
#define COMMANDS_CPP

#include "Commands.h"
#include "ELF.h"

unsigned int Call::get_byte_num () const {
    return byte_num;
}

void Call::write_to_buf (char* buf) const {
    *buf = 0xe8;
    *reinterpret_cast<QWORD*> (buf + 1) = offset;
}

#endif //COMMANDS_CPP
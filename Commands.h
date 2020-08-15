#ifndef COMMANDS_H
#define COMMANDS_H

#include "Types.h"

enum REGS {
    RAX,
    RCX,
    RDX,
    RBX,
    RSP,
    RBP,
    RSI,
    RDI
};

unsigned int RM_REG_by_registers (unsigned int to, unsigned int from) {
    return to + (from << 3);
}


class Command {
public:
    virtual void write_to_buf (unsigned char* buf) const = 0; 
    virtual unsigned int get_byte_num () const = 0;

    virtual ~Command () {};
};


class Code {
    unsigned char* buf;
    unsigned char* buf_ptr;
    unsigned int size;
public:
    Code (unsigned int buf_size);
    Code (const unsigned char* _buf, const unsigned int buf_size);
    Code (const Code& other);
    ~Code ();
    unsigned int get_size () const;
    unsigned char* get_code_buf    () const;
    void write_from_buf   (unsigned char* _buf, unsigned int num);
    void add_command  (const Command& command);
};

class REX {
public:
    BYTE data;
public:
    REX (bool W, bool R = 0, bool X = 0, bool B = 0)
    : data (0b01000000 | (W << 3) | (R << 2) | (X << 1) | B) {}
    //explicit REX (BYTE _data) : data (_data) {}
    
};

class OpCode {
    BYTE data;
public:
    explicit OpCode (BYTE _data) : data (_data) {};
};

class ModRM {
    BYTE data;
public:
    ModRM (unsigned int Mod, unsigned int Reg, unsigned int RM = 0U)
    : data ((Mod << 6) | (Reg << 3) | RM) {}
};


class Call : public Command {
    unsigned int byte_num;
    unsigned int offset;
public:
    Call (unsigned int _offset) : byte_num (5), offset (_offset) {};
    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};


class Mov64_RR : public Command {
    unsigned int byte_num;
    unsigned int to;
    unsigned int from;
public:
    Mov64_RR (unsigned int _to, unsigned int _from)
    : to (_to), from (_from), byte_num (3) {}

    void write_to_buf (unsigned char* buf) const override {
        set_elems (buf,  REX (1) , OpCode (0x89) , ModRM (0b11, RM_REG_by_registers (to, from)));
    }

    unsigned int get_byte_num () const override {return byte_num;}
};

#endif //COMMANDS_H
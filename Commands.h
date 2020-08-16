#ifndef COMMANDS_H
#define COMMANDS_H

#include "Types.h"

namespace REGS {
    enum Registers {
        RAX,
        RCX,
        RDX,
        RBX,
        RSP,
        RBP,
        RSI,
        RDI
    };
};

unsigned int RM_REG_by_registers (unsigned int to, unsigned int from);

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
    REX (BYTE W, BYTE R = 0, BYTE X = 0, BYTE B = 0)
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
    ModRM (BYTE Mod, BYTE Reg, BYTE RM = 0U)
    : data ((Mod << 6) + Reg + RM) {}
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
    : byte_num (3), to (_to), from (_from) {}

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class Mov64_RM : public Command {
    unsigned int byte_num;
    unsigned int to;
    int from_offset;
    
public:

    Mov64_RM (unsigned int _to, int _from_offset);
    Mov64_RM () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class Mov64_MR : public Command {
    unsigned int byte_num;
    unsigned int to;
    int from_offset;
    
public:

    Mov64_MR (int _from_offset, unsigned int _to);
    Mov64_MR () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class Mov64_MImm : public Command {
    unsigned int byte_num;
    int from_offset;
    int imm;
    
public:

    Mov64_MImm (int _from_offset, int _imm);
    Mov64_MImm () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};





class Mov64_RImm : public Command {
    unsigned int byte_num;
    unsigned int to;
    int imm;
    
public:

    Mov64_RImm (unsigned int _to, int _imm);
    Mov64_RImm () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};

#endif //COMMANDS_H
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
        RDI,
        R8,
        R9,
        R10,
        R11,
        R12,
        R13,
        R14,
        R15
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
    unsigned char* get_code_buf_ptr    () const;
    void write_from_buf   (unsigned char* _buf, unsigned int num);
    void add_command  (const Command& command);
};

class REX {
public:
    BYTE data;
public:
    REX (BYTE W, BYTE R = 0U, BYTE X = 0U, BYTE B = 0U)
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
    int mem_offset;
    
public:

    Mov64_RM (unsigned int _to, int _mem_offset);
    Mov64_RM () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class Mov64_MR : public Command {
    unsigned int byte_num;
    unsigned int to;
    int mem_offset;
    
public:

    Mov64_MR (int _mem_offset, unsigned int _to);
    Mov64_MR () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class Mov64_MImm : public Command {
    unsigned int byte_num;
    int mem_offset;
    int imm;
    
public:

    Mov64_MImm (int _mem_offset, int _imm);
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



class PushM : public Command {
    unsigned int byte_num;
    int mem_offset;
    
public:

    PushM (int _mem_offset);
    PushM () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class PushImm : public Command {
    unsigned int byte_num;
    int imm;
    
public:

    PushImm (int _imm);
    PushImm () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};


class PushR : public Command {
    unsigned int byte_num;
    unsigned int reg;
    
public:

    PushR (unsigned int _reg);
    PushR () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};


class PopR : public Command {
    unsigned int byte_num;
    unsigned int reg;
    
public:

    PopR (unsigned int _reg);
    PopR () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class Add64_RR : public Command {
    unsigned int byte_num;
    unsigned int to;
    unsigned int from;
public:
    Add64_RR (unsigned int _to, unsigned int _from)
    : byte_num (3), to (_to), from (_from) {}

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};


class Add64_RM : public Command {
    unsigned int byte_num;
    unsigned int to;
    int mem_offset;
    
public:

    Add64_RM (unsigned int _to, int _mem_offset);
    Add64_RM () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class Add64_RImm : public Command {
    unsigned int byte_num;
    unsigned int to;
    int imm;
    
public:

    Add64_RImm (unsigned int _to, int _imm);
    Add64_RImm () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class Sub64_RImm : public Command {
    unsigned int byte_num;
    unsigned int to;
    int imm;
    
public:

    Sub64_RImm (unsigned int _to, int _imm);
    Sub64_RImm () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};




class Sub64_RM : public Command {
    unsigned int byte_num;
    unsigned int to;
    int mem_offset;
    
public:

    Sub64_RM (unsigned int _to, int _mem_offset);
    Sub64_RM () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class Sub64_RR : public Command {
    unsigned int byte_num;
    unsigned int to;
    unsigned int from;
public:
    Sub64_RR (unsigned int _to, unsigned int _from)
    : byte_num (3), to (_to), from (_from) {}

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class Idiv_R : public Command {
    unsigned int byte_num;
    unsigned int reg;
    
public:

    Idiv_R (unsigned int _reg);
    Idiv_R () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class Ret : public Command {
    unsigned int byte_num;
    
public:

    Ret ();

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class Itoa : public Command {
    unsigned int byte_num;
public:

    Itoa ();

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};

class GStart : public Command {
    unsigned int byte_num;
public:

    GStart ();

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class OutputRBX : public Command {
    unsigned int byte_num;
    unsigned char* addr_of_itoa;
public:

    OutputRBX (unsigned char* _addr_of_itoa);

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};




#endif //COMMANDS_H
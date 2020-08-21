#ifndef COMMANDS_H
#define COMMANDS_H

#include "Types.h"
#include "my_vector.h"

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

class Request {
 public:
    const char* label;
    unsigned char* address;

    Request (const char* _label, unsigned char* _address) : label (_label), address (_address) {};
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

class SIB {
    BYTE data;
public:
    SIB (BYTE Scale, BYTE Index, BYTE Base)
    : data ((Scale << 6) | (Index << 3) | Base) {}
};



class Call : public Command {
    unsigned int byte_num = 5;
    unsigned int offset = 0;
    Vector <Request>* label_requests = nullptr;
    const char* func_name;
public:
    Call (unsigned int _offset) : offset (_offset) {};
    Call (const char* _func_name, Vector <Request>* _label_requests) 
    : func_name (_func_name), label_requests (_label_requests) {};
    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};


class Je : public Command {
    unsigned int byte_num = 6;
    unsigned int offset = 0;
    Vector <Request>* label_requests = nullptr;
    const char* cond_name;
public:
    Je (unsigned int _offset) : offset (_offset) {};
    Je (const char* _cond_name, Vector <Request>* _label_requests) 
    : cond_name (_cond_name), label_requests (_label_requests) {};
    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class Jne : public Command {
    unsigned int byte_num = 6;
    unsigned int offset = 0;
    Vector <Request>* label_requests = nullptr;
    const char* cond_name;
public:
    Jne (unsigned int _offset) : offset (_offset) {};
    Jne (const char* _cond_name, Vector <Request>* _label_requests) 
    : cond_name (_cond_name), label_requests (_label_requests) {};
    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class Jg : public Command {
    unsigned int byte_num = 6;
    unsigned int offset = 0;
    Vector <Request>* label_requests = nullptr;
    const char* cond_name;
public:
    Jg (unsigned int _offset) : offset (_offset) {};
    Jg (const char* _cond_name, Vector <Request>* _label_requests) 
    : cond_name (_cond_name), label_requests (_label_requests) {};
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

class Mov64_RAddr : public Command {
    unsigned int byte_num;
    unsigned int to;
    unsigned int addr;
    
public:

    Mov64_RAddr (unsigned int _to, unsigned int _addr) : byte_num (8), to (_to), addr (_addr) {};
    Mov64_RAddr () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};

class Mov64_AddrR : public Command {
    unsigned int byte_num;
    unsigned int addr;
    unsigned int from;

public:

    Mov64_AddrR (unsigned int _addr, unsigned int _from) : byte_num (8), addr (_addr) , from (_from) {};
    Mov64_AddrR () = delete;

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


class Imul64_RImm : public Command {
    unsigned int byte_num;
    unsigned int to;
    int imm;
    
public:

    Imul64_RImm (unsigned int _to, int _imm);
    Imul64_RImm () = delete;

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};


class Imul64_RR : public Command {
    unsigned int byte_num;
    unsigned int to;
    unsigned int from;
public:
    Imul64_RR (unsigned int _to, unsigned int _from)
    : byte_num (4), to (_to), from (_from) {}

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

class Atoi : public Command {
    unsigned int byte_num;
public:

    Atoi ();

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




class InputRAX : public Command {
    unsigned int byte_num;
    unsigned char* addr_of_atoi;
public:

    InputRAX (unsigned char* _addr_of_atoi);

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};


class Sqrt : public Command {
    unsigned int byte_num;
public:

    Sqrt ();

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};



class Cmp_RR : public Command {
    unsigned int byte_num;
    unsigned int to;
    unsigned int from;
public:
    Cmp_RR (unsigned int _to, unsigned int _from)
    : byte_num (3), to (_to), from (_from) {}

    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};




#endif //COMMANDS_H
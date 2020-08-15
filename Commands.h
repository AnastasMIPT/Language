#ifndef COMMANDS_H
#define COMMANDS_H

#include "Types.h"

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
    REX (bool W, bool R, bool X, bool B)
    : data (0b01000000 | (W << 3) | (R << 2) | (X << 1) | B) {}
    
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
public:
    Mov64_RR (unsigned int to, unsigned int from) {
       
    }

    void write_to_buf (unsigned char* buf) const override {
        //set_elem (buf,  REX (1) , OpCode (89) , RM (0x11, to, from));
    }

};

#endif //COMMANDS_H
#ifndef COMMANDS_H
#define COMMANDS_H


class Command {
public:
    virtual void write_to_buf (char* buf) const = 0; 
    virtual unsigned int get_byte_num () const = 0;
};

class Call : public Command {
    unsigned int byte_num;
    unsigned int offset;
public:
    Call (unsigned int _offset) : byte_num (5), offset (_offset) {};
    void write_to_buf (char* buf) const;
    unsigned int get_byte_num () const;
};


#endif //COMMANDS_H
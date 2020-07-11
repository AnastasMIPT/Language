#ifndef COMMANDS_H
#define COMMANDS_H



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


class Call : public Command {
    unsigned int byte_num;
    unsigned int offset;
public:
    Call (unsigned int _offset) : byte_num (5), offset (_offset) {};
    void write_to_buf (unsigned char* buf) const override;
    unsigned int get_byte_num () const override;
};


#endif //COMMANDS_H
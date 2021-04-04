#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include "Words.h"
#include "Func_s.h"
#include "Func_b.h"
#include "ELF.h"
#include "Commands.h"
#include "hash_table.h"
#include "my_vector.h"


#define DEBUG

#ifdef DEBUG
    #define DEB_INFO printf ("DEBUG_INFO:  Called from FILE: %s from FUNCTION: %s   LINE: %d\n", __FILE__, __func__, __LINE__);
#else 
    #define DEB_INFO ;
#endif





#define _NewEl(type)                                       \
else if ( strcmp (#type, data) == 0)                                      \
    root =  CreateNode (type, #type, nullptr, nullptr);    \


#define _NewTerm(dat, type)   \
else if (strcmp (dat, data) == 0)                   \
    root = CreateNode (type, data, nullptr, nullptr);      \


#define _KEYWORD(type) CreateNode (type, #type, nullptr, nullptr)
#define _Lf root->left
#define _R  root->right


constexpr int DataSize = 50;
constexpr int NullFunc = FUNCCOL - COL_WORDS - 1;
constexpr int ColVarsInOneFunc = 30;
constexpr int VarNum = 40;
constexpr int Bytes = 8;
constexpr int Precision = 100;
constexpr int SizeOfCode = 64;
constexpr unsigned int Addr_sqrt_from = 0x600151;
constexpr unsigned int Addr_sqrt_res  = 0x600159;



using HashTable_t = HashTable <unsigned char*>;

int IfNumber = 0;


struct Node
{
    char* data;
    double num;
    Node* left;
    Node* right;
    int type;
};



Node* GetTreeFromFile (Node* root, FILE* f_in);

/*! Функция, создающая новый узел
*
*	@param[in] type Тип узла
*	@param[in] data Символ оператора
*	@param[in] left Указатель на левое поддерево
*	@param[in] right Указатель на правое поддерево
*
*	@return Указатель на созданный узел
*
*/
Node* CreateNode (int type, const char* data, Node* left, Node* right, double num);
Node* CreateNode (int type, const char* data, Node* left, Node* right);
Node* CreateNode (double num);

//void ProgramToASM (Node* root, FILE* f_out, int ret_value = UNDEF);
void ProgramToBinary (Node* root, Code& code, HashTable_t& labels, 
                      Vector<Request>& requests, const char* path_ex_file, int ret_value = UNDEF);

int ReduseRsp (Node* root);

int Hash (const char* str);

void Arithmetic_op_sum_b (Node* root, Code& code, HashTable_t& labels, 
                          Vector<Request>& requests, const char* path_ex_file, int ret_value);
void Arithmetic_op_mul_b (Node* root, Code& code, HashTable_t& labels, 
                          Vector<Request>& requests, const char* path_ex_file, int ret_value);
void Arithmetic_op_div_b (Node* root, Code& code, HashTable_t& labels, 
                          Vector<Request>& requests, const char* path_ex_file, int ret_value);
void Arithmetic_op_sub_b (Node* root, Code& code, HashTable_t& labels, 
                          Vector<Request>& requests, const char* path_ex_file, int ret_value);

void Handle_call_b       (Node* root, Code& code, Vector <Request>& requests, int ret_value);
void Handle_sqrt_b       (Node* root, Code& code, HashTable_t& labels, 
                          Vector<Request>& requests, const char* path_ex_file, int ret_value);
void Handle_assign_b     (Node* root, Code& code, HashTable_t& labels, 
                          Vector<Request>& requests, const char* path_ex_file);
// void Handle_start_b      (Node* root, const char* path_ex_file, const HashTable <unsigned char*>& labels);
// void Handle_ret_b        (Node* root, const char* path_ex_file);
void Handle_comma_b      (Node* root, Code& code, HashTable_t& labels, Vector <Request>& requests,
                          const char* path_ex_file, int ret_value);
void Handle_def_b        (Node* root, Code& code, HashTable_t& labels);


/*! Функция переводящая получаемое целое число в строку
*	@param[in] string Cтрока, в которую будет записан результат
*	@param[in] base   Основание системы счисления
*	
*	@return Целое число
*
*/
char * Itoa (int value, char * string, int base = 10);
/*! Функция зеркально отображающая строку относительно среднего элемента
*	@param [in] string Cтрока
*	@param [in] size Фактический размер строки
*
*	@return Отображенная строка
*
*/
char * reverse_string (char * string, int size);



void Handle_of_label_requests (const Vector <Request>& requests, const HashTable <unsigned char*>& labels);

int main () {

    FILE* f_in = fopen ("./resources/tree.txt", "r");
    assert (f_in);

    Node* root = {};
    root = GetTreeFromFile (root, f_in);
    fclose (f_in);

    Vector <Request> label_requests;
    HashTable <unsigned char*> labels (1009, CRC_32_fast);
    Code code (2048);
    ProgramToBinary (root, code, labels, label_requests, "./resources/ASMx86/my_elf");

    return 0;
}

void Handle_of_label_requests (const Vector <Request>& requests, const HashTable_t& labels) {
    for (int i = 0; i < requests.size (); ++i) {
        auto cur_label = labels.find (requests[i].label);
        if (cur_label) {
            unsigned int offset = cur_label->second - (requests[i].address + 4);
            *reinterpret_cast<unsigned int*> (requests[i].address) =  offset;
        } else {
            printf ("ERROR: label \'%s\' wasn't found\n", requests[i].label);
        }
    }
}


void ProgramToBinary (Node* root, Code& code, HashTable_t& labels, Vector<Request>& requests, 
                      const char* path_ex_file, int ret_value) {
    if (!root) return;

    
    

    int label_number = 0;
    switch (root->type) {
        case START:
            {
            //Handle_start_b    (root, path_ex_file);
            code.add_command (Cmd::Call ("main", &requests));
            code.add_command (Cmd::GStart ());

            labels.insert ("itoa", code.get_code_buf_ptr ());
            code.add_command (Cmd::Itoa ());
            labels.insert ("atoi", code.get_code_buf_ptr ());
            code.add_command (Cmd::Atoi ());
            
            
            ProgramToBinary (_R , code, labels, requests, path_ex_file);

            DEB_INFO
            Handle_of_label_requests (requests, labels);
            DEB_INFO
            ELF file (code);
            DEB_INFO
            file.load_to_file (path_ex_file);
            DEB_INFO
            break;
            }
        case D:
            ProgramToBinary (_R , code, labels, requests, path_ex_file);
            ProgramToBinary (_Lf, code, labels, requests, path_ex_file);
            break;
        case DEF:
            Handle_def_b     (root, code, labels);
            ProgramToBinary (_R , code, labels, requests, path_ex_file);
            break;
        case FUNC:
            ProgramToBinary (_R , code, labels, requests, path_ex_file);
            break;
        case CALL:
            ProgramToBinary (_Lf, code, labels, requests, path_ex_file, ret_value);
            Handle_call_b    (root, code, requests, ret_value);
            break;
        case COMMA:
            Handle_comma_b   (root, code, labels, requests, path_ex_file, ret_value);
            break;
        case B:
            ProgramToBinary (_R , code, labels, requests, path_ex_file);
            break;
        case OP:
            ProgramToBinary (_R , code, labels, requests, path_ex_file);
            ProgramToBinary (_Lf, code, labels, requests, path_ex_file);
            break;
        case ASSIGN:
            Handle_assign_b  (root, code, labels, requests, path_ex_file);
            break;
        case IF:
            {
            label_number = IfNumber;
            ProgramToBinary (_Lf, code, labels, requests, path_ex_file);
            IfNumber++;
            ProgramToBinary (_R , code, labels, requests, path_ex_file);
            char * label = (char*) calloc (10, sizeof (char));
            labels.insert (Itoa (label_number, label), code.get_code_buf_ptr ());
            // fprintf (f_out, "end_if%d:\n", buf);
            break;
            }
        case EQUAL:
            {
            ProgramToBinary (_Lf, code, labels, requests, path_ex_file, REGS::RCX);
            ProgramToBinary (_R , code, labels, requests, path_ex_file, REGS::RDX);
            code.add_command (Cmd::Cmp_RR (REGS::RCX, REGS::RDX));
            
            char * label = (char*) calloc (10, sizeof (char));
            code.add_command (Cmd::Jne (Itoa (IfNumber, label), &requests));
            //free (label);
            // fprintf (f_out, "\t\tcmp RCX, RDX\n"
            //                "\t\tjne end_if%d\n", IfNumber);
            break;
            }
        case UNEQUAL:
            {
            ProgramToBinary (_Lf, code, labels, requests, path_ex_file, REGS::RCX);
            ProgramToBinary (_R , code, labels, requests, path_ex_file, REGS::RDX);
            code.add_command (Cmd::Cmp_RR (REGS::RCX, REGS::RDX));

            char * label = (char*) calloc (10, sizeof (char));
            code.add_command (Cmd::Je (Itoa (IfNumber, label), &requests));
            //free (label);
            // fprintf (f_out, "\t\tcmp RCX, RDX\n"
            //                "\t\tje end_if%d\n", IfNumber);
            break;
            }
        case MORE:
            {
            ProgramToBinary (_R , code, labels, requests, path_ex_file, REGS::RCX);
            ProgramToBinary (_Lf, code, labels, requests, path_ex_file, REGS::RDX);
            code.add_command (Cmd::Cmp_RR (REGS::RCX, REGS::RDX));


            char * label = (char*) calloc (10, sizeof (char));
            code.add_command (Cmd::Jg (Itoa (IfNumber, label), &requests));
            //free (label);
            // fprintf (f_out, "\t\tcmp RCX, RDX\n"
            //                "\t\tjg end_if%d\n", IfNumber);
            break;
            }
        case SUM:
            Arithmetic_op_sum_b (root , code, labels, requests, path_ex_file, ret_value);
            break;
        case SUB:
            Arithmetic_op_sub_b (root , code, labels, requests, path_ex_file, ret_value);
            break;
        case MUL:
            Arithmetic_op_mul_b (root , code, labels, requests, path_ex_file, ret_value);
            break;
        case DIV:
            Arithmetic_op_div_b (root , code, labels, requests, path_ex_file, ret_value);
            break;
        case RETURN:
            DEB_INFO
            ProgramToBinary (_R , code, labels, requests, path_ex_file, REGS::RCX);
            DEB_INFO
            code.add_command (Cmd::Mov64_RR (REGS::RAX, REGS::RCX));
            code.add_command (Cmd::Mov64_RR (REGS::RSP, REGS::RBP));
            code.add_command (Cmd::PopR (REGS::RBP));
            code.add_command (Cmd::Ret ());
            break;
        case OUTPUT:
            DEB_INFO
            ProgramToBinary (_R , code, labels, requests, path_ex_file, REGS::RBX);
            DEB_INFO
            assert (labels.find ("itoa"));
            code.add_command (Cmd::OutputRBX (labels.find("itoa")->second));
            
            break;
        case INPUT:
            code.add_command (Cmd::InputRAX  (labels.find ("atoi")->second));
            code.add_command (Cmd::Imul64_RImm (REGS::RAX, Precision));
            code.add_command (Cmd::Mov64_MR (Bytes * static_cast<int> (_R->num), REGS::RAX));
            // fprintf (path_ex_file, "\n\t\t;input\n\n");
            // fprintf (path_ex_file, input_s);
            // fprintf (path_ex_file, "\t\timul rax, %d\n"
            //                "\t\tmov qword [rbp%+d], rax\n\n", Precision, Bytes * static_cast<int> (_R->num));
            break;
        case SQRT:
            Handle_sqrt_b (root , code, labels, requests, path_ex_file, ret_value);
            break;  
        case BREAK:
            ProgramToBinary (_R , code, labels, requests, path_ex_file);
            // fprintf (path_ex_file, "\t\tBREAK\n");
            break;
        case DIFF:
            ProgramToBinary (_R , code, labels, requests, path_ex_file);
            // fprintf (path_ex_file, "\t\tDIFF\n");
            break;
        case VAR:
            if (ret_value != UNDEF) {
                code.add_command (Cmd::Mov64_RM (reg_for_math_b[ret_value], Bytes * static_cast<int> (root->num)));    
            } 
            break;
        case NUM:
            if (ret_value != UNDEF) {
                code.add_command (Cmd::Mov64_RImm (reg_for_math_b[ret_value], Precision * static_cast<int> (root->num)));
            }
            break;
        default:
            printf ("\n! ERROR ! Неизвестный узел %s, тип: %d", root->data, root->type);
            break;
    }
    
}

void RedusePrecision (Node* elem, Code& code, int ret_value) {
    if (ret_value != UNDEF) {
        code.add_command (Cmd::Mov64_RR (REGS::RAX, reg_for_math_b[ret_value]));
        code.add_command (Cmd::Mov64_RImm (REGS::R15, Precision));
        code.add_command (Cmd::Cqo ());
        code.add_command (Cmd::Idiv_R (REGS::R15));
        code.add_command (Cmd::Mov64_RR (reg_for_math_b[ret_value], REGS::RAX));
        
    } else {
        if (elem->type == VAR) {
            int var_offset = Bytes * static_cast<int> (elem->num);

            code.add_command (Cmd::Mov64_RM (REGS::RAX, var_offset));
            code.add_command (Cmd::Mov64_RImm (REGS::R15, Precision));
            code.add_command (Cmd::Cqo ());
            code.add_command (Cmd::Idiv_R (REGS::R15));
            code.add_command (Cmd::Mov64_MR (var_offset, REGS::RAX));

        }
    }
}

// void Handle_start_b      (Node* root, const char* path_ex_file) {
    
//     // code2.add_command (Cmd::GStart ());
//     // labels.insert ("itoa", code2.get_code_buf_ptr ());
//     // printf ("itoa the first pointer %p\n", code2.get_code_buf_ptr ());
//     // code2.add_command (Cmd::Itoa ());
//     // printf ("atoi the first pointer %p\n", code2.get_code_buf_ptr ());
//     // labels.insert ("atoi", code2.get_code_buf_ptr ());
//     // code2.add_command (Cmd::Atoi ());
//     // labels.insert ("main", code2.get_code_buf_ptr ());


//     fprintf (f_out, start_s);
//     fprintf (f_out, itoa_s);
//     fprintf (f_out, atoi_s);

//     ProgramToASM (_R , f_out);
    
//     fprintf (f_out, data_s);
//     fprintf(f_out, "\t\tSYMB_POINT equ %d\n", static_cast<int> (log10 (Precision)));

// }

// void Handle_ret_b        (Node* root, const char* path_ex_file) {

//     fprintf (f_out, "\n\t\t;return\n\n");

//     ProgramToASM (_R , f_out, RBX);
    
//     fprintf (f_out, "\t\tmov rax, rbx\n");
//     fprintf (f_out, ret_s);
// }

void Handle_comma_b      (Node* root, Code& code, HashTable_t& labels, Vector <Request>& requests,
                          const char* path_ex_file, int ret_value) {

    ProgramToBinary (_Lf , code, labels, requests, path_ex_file);
    
    if (_R->type == NUM) {
        
        code.add_command (Cmd::PushImm (Precision * static_cast<int> (_R->num))); 
    
    } else if (_R->type == VAR) {
        
        code.add_command (Cmd::PushM (Bytes * static_cast<int> (_R->num)));

    } else {
        ProgramToBinary (_R , code, labels, requests, path_ex_file, REGS::RCX);
        code.add_command (Cmd::PushR (reg_for_math_b[ret_value]));
    }
}

void Handle_def_b        (Node* root, Code& code, HashTable_t& labels) {
    
    labels.insert (_R->data, code.get_code_buf_ptr ());
    printf ("FUNC###########################     %s\n", _R->data);
    code.add_command (Cmd::PushR (REGS::RBP));
    code.add_command (Cmd::Mov64_RR (REGS::RBP, REGS::RSP));
    code.add_command (Cmd::Sub64_RImm (REGS::RSP, Bytes * static_cast<int> (_R->left->num)));

}

void Handle_call_b       (Node* root, Code& code, Vector <Request>& requests, int ret_value) {

    code.add_command (Cmd::Call (_R->data, &requests));
    code.add_command (Cmd::Add64_RImm (REGS::RSP, Bytes * ReduseRsp (_Lf)));
    //printf ("WWWWW %d\n", ret_value);

    if (ret_value != REGS::RAX && ret_value != UNDEF) {  
        code.add_command (Cmd::Mov64_RR (reg_for_math_b[ret_value], REGS::RAX));
    }
}

void Handle_assign_b     (Node* root, Code& code, HashTable_t& labels, 
                          Vector<Request>& requests, const char* path_ex_file) {

    if (_R->type == NUM) {
        code.add_command (Cmd::Mov64_MImm (Bytes * static_cast<int> (_Lf->num), Precision * static_cast<int> (_R->num)));
        DEB_INFO

    } else if (_R->type == CALL) {

        ProgramToBinary (_R , code, labels, requests, path_ex_file, REGS::RAX);
        code.add_command (Cmd::Mov64_MR (Bytes * static_cast<int> (_Lf->num), REGS::RAX));
    
    } else {
    
        ProgramToBinary (_R , code, labels, requests, path_ex_file, REGS::RCX);
        code.add_command (Cmd::Mov64_MR (Bytes * static_cast<int> (_Lf->num), REGS::RCX));
    
    }
}

void Handle_sqrt_b       (Node* root, Code& code, HashTable_t& labels, 
                          Vector<Request>& requests, const char* path_ex_file, int ret_value) {

    ProgramToBinary (_R , code, labels, requests, path_ex_file, ret_value);

    code.add_command (Cmd::Mov64_AddrR (Addr_sqrt_from, reg_for_math_b[ret_value]));
    code.add_command (Cmd::Sqrt ());
    code.add_command (Cmd::Mov64_RAddr (reg_for_math_b[ret_value], Addr_sqrt_res));
    code.add_command (Cmd::Imul64_RImm (reg_for_math_b[ret_value], static_cast<int> (sqrt (Precision))));

}



void Arithmetic_op_mul_b (Node* root, Code& code, HashTable_t& labels, 
                          Vector<Request>& requests, const char* path_ex_file, int ret_value) {
    
    if (_Lf->type == NUM) {
    
        ProgramToBinary (_R, code, labels, requests, path_ex_file, ret_value);
        code.add_command (Cmd::Imul64_RImm (reg_for_math_b[ret_value], static_cast<int> (_Lf->num)));

    } else if (_R->type == NUM) {
    
        ProgramToBinary (_Lf, code, labels, requests, path_ex_file, ret_value);
        code.add_command (Cmd::Imul64_RImm (reg_for_math_b[ret_value], static_cast<int> (_R->num)));
    
    } else {
        assert (ret_value + 1 < UNDEF);
        ProgramToBinary (_Lf, code, labels, requests, path_ex_file, ret_value);
        RedusePrecision (_Lf, code, ret_value);

        ProgramToBinary (_R, code, labels, requests, path_ex_file, ret_value + 1);

        
        
        code.add_command (Cmd::Imul64_RR (reg_for_math_b[ret_value], reg_for_math_b[ret_value + 1]));

    }
}

void Arithmetic_op_div_b (Node* root, Code& code, HashTable_t& labels, 
                          Vector<Request>& requests, const char* path_ex_file, int ret_value) {
    
    assert (ret_value + 1 < UNDEF);
    assert (root);

    ProgramToBinary (_Lf, code, labels, requests, path_ex_file, ret_value);
        
    if (_R->type == NUM) {
        code.add_command (Cmd::Mov64_RImm (reg_for_math_b[ret_value + 1], _R->num));
        
    
    } else {

        ProgramToBinary (_R, code, labels, requests, path_ex_file, ret_value + 1);
        RedusePrecision (_R, code,  ret_value + 1);
    }
    
    code.add_command (Cmd::Mov64_RR (REGS::RAX, reg_for_math_b[ret_value]));
    code.add_command (Cmd::Cqo ());
    code.add_command (Cmd::Idiv_R (reg_for_math_b[ret_value + 1]));
    
    if (ret_value != REGS::RAX) {

        code.add_command (Cmd::Mov64_RR (reg_for_math_b[ret_value], REGS::RAX));
    }
}

void Arithmetic_op_sub_b (Node* root, Code& code, HashTable_t& labels, 
                          Vector<Request>& requests, const char* path_ex_file, int ret_value) {
    
    ProgramToBinary (_Lf, code, labels, requests, path_ex_file, ret_value);

    if (_R->type == NUM) {

        code.add_command (Cmd::Sub64_RImm (reg_for_math_b[ret_value], Precision * static_cast<int> (_R->num)));

    } else if (_R->type == VAR) {
        
        code.add_command (Cmd::Sub64_RM (reg_for_math_b[ret_value], Bytes * static_cast<int> (_R->num)));
    } else {
        
        assert (ret_value + 1 < UNDEF);
        ProgramToBinary (_R, code, labels, requests, path_ex_file, ret_value + 1);
        code.add_command (Cmd::Sub64_RR (reg_for_math_b[ret_value], reg_for_math_b[ret_value + 1]));
    
    }
}

void Arithmetic_op_sum_b (Node* root, Code& code, HashTable_t& labels, 
                          Vector<Request>& requests, const char* path_ex_file, int ret_value) {
    if (_Lf->type == VAR || _Lf->type == NUM) {
        
        ProgramToBinary (_R, code, labels, requests, path_ex_file, ret_value);
        
        if (_Lf->type == VAR) {
            code.add_command (Cmd::Add64_RM (reg_for_math_b[ret_value], Bytes * static_cast<int> (_Lf->num)));
            
        }
        if (_Lf->type == NUM)
            code.add_command (Cmd::Add64_RImm (reg_for_math_b[ret_value], Precision * static_cast<int> (_Lf->num)));

    } else if (_R->type == VAR || _R->type == NUM) {
        
        ProgramToBinary (_Lf, code, labels, requests, path_ex_file, ret_value);
        
        if (_R->type == VAR)
            code.add_command (Cmd::Add64_RM (reg_for_math_b[ret_value], Bytes * static_cast<int> (_R->num)));
        if (_R->type == NUM)
            code.add_command (Cmd::Add64_RImm (reg_for_math_b[ret_value], Precision * static_cast<int> (_R->num)));
    
    } else {
    
        ProgramToBinary (_Lf, code, labels, requests, path_ex_file, ret_value);
        assert (ret_value + 1 < UNDEF);
        ProgramToBinary (_R, code, labels, requests, path_ex_file, ret_value + 1);
        code.add_command (Cmd::Add64_RR (reg_for_math_b[ret_value], reg_for_math_b[ret_value + 1]));
    
    }


}

int ReduseRsp (Node* root) {
    if (!_R) return 0;
    int col = 1;
    Node* ptr = root;
    while (ptr->left)
    {
        col++;
        ptr = ptr->left;
    }
    return col;
}

Node* GetTreeFromFile (Node* root, FILE* f_in) {

    fscanf (f_in, "(");
    char* data = (char*) calloc (DataSize, sizeof (char));
    int n = 0;
    fscanf (f_in, "%[^()]%n", data, &n);
    if (n == 0) {
        fscanf (f_in,")");
        return nullptr;
    }
    if (strcmp ("START", data)  == 0)
        root =  _KEYWORD (START);
    _NewEl (OP)
    _NewEl (D)
    _NewEl (B)
    _NewEl (END)
    _NewEl (IF)
    _NewEl (WHILE)
    _NewEl (BLOCK_ST)
    _NewEl (BLOCK_END)
    _NewEl (SKOBKA1)
    _NewEl (SKOBKA2)
    _NewEl (ASSIGN)
    _NewEl (DEF)
    _NewEl (EQUAL)
    _NewEl (UNEQUAL)
    _NewEl (MORE)
    _NewEl (COMMA_POINT)
    _NewEl (RETURN)
    _NewEl (INPUT)
    _NewEl (OUTPUT)
    _NewEl (CALL)
    _NewTerm ("+", SUM)
    _NewTerm ("-", SUB)
    _NewTerm ("*", MUL)
    _NewTerm ("/", DIV)
    _NewTerm ("'='", ASSIGN)
    _NewTerm (",", COMMA)
    else if (strcmp (data, "sqrt") == 0) {
        root = CreateNode (SQRT, "sqrt", nullptr, nullptr);
    }
    else if (*data == '@') {
        data++;
        int col = 0;
        double num = 0.0;
        sscanf (data, "%lf%n", &num, &col);
        data += col;
        char* dat = (char*) calloc (DataSize, sizeof(char));
        sscanf (data, "%s", dat);
        root = CreateNode (VAR, dat, nullptr, nullptr, num);
    }
    else if (('0' <= *data && *data <= '9') || *data == '-') {
        double  val = 0;
        int col = 0;
        sscanf (data, "%lf%n", &val, &col);
        data += col;
        root = CreateNode (val);
    }
    else {

        int col = 0;
        double num = 0.0;
        sscanf (data, "%lf%n", &num, &col);
        data += col;
        char* dat = (char*) calloc (DataSize, sizeof(char));
        sscanf (data, "%s", dat);
        root = CreateNode (FUNC, dat, nullptr, nullptr, num);
    }
    //else
    //  root = CreateNode (0, "ERROR", nullptr, nullptr);
    printf ("%s  %d\n", data, Hash (data));

    root->left  = GetTreeFromFile (root->left,  f_in);
    root->right = GetTreeFromFile (root->right, f_in);
    fscanf (f_in, ")");
    return root;
}

int Hash (const char* str) {
    int hash = 0;

    for (char* p = const_cast<char*> (str); *p != '\0'; p++)
        hash = 3 * hash + (*p >> 3 | 1233) + *p;

    return hash;
}

Node* CreateNode (int type, const char* data, Node* left, Node* right) {

    Node* node  = (Node*) calloc (1, sizeof (Node));
    node->data  = (char*) calloc (DataSize, sizeof (char));
    strcpy (node->data, data);
    node->left  = left;
    node->right = right;
    node->type  = type;


    return node;
}

Node* CreateNode (int type, const char* data, Node* left, Node* right, double num) {

    Node* node  = (Node*) calloc (1, sizeof (Node));
    node->data  = (char*) calloc (DataSize, sizeof (char));
    strcpy (node->data, data);
    node->left  = left;
    node->right = right;
    node->type  = type;
    node->num = num;

    return node;
}

Node* CreateNode (double num) {
    Node* node  = (Node*) calloc (1, sizeof (Node));
    node->num  = num;
    node->left  = nullptr;
    node->right = nullptr;
    node->type  = NUM;

    return node;
}

char * reverse_string (char * string, int size)
{
	assert (size > 0);
	assert (string != nullptr);

	
	int buf = '0';
	int median = size / 2;
	if (string[size] == '\n' || string[size] == '\0') size -= 1;

	for (int i = 0; i != median; i++) {
		buf = string[i];
		string[i] = string[size - i];
		string[size - i] = buf; 
	}
	
		
	return string;
}


char * Itoa (int value, char * string, int base)
{
    assert (base > 0);
	char * begin = string;
	while (value != 0) {
		*string = value % base + '0';
		value /= base;
		string++;
	}
	
	return reverse_string (begin, 2);
}
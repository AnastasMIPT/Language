#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include "Words.h"
#include "Func_s.h"

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
*	@param [in] type Тип узла
*	@param [in] data Символ оператора
*	@param [in] left Указатель на левое поддерево
*	@param [in] right Указатель на правое поддерево
*
*	@return Указатель на созданный узел
*
*/
Node* CreateNode (int type, const char* data, Node* left, Node* right, double num);
Node* CreateNode (int type, const char* data, Node* left, Node* right);
Node* CreateNode (double num);

void ProgramToASM (Node* root, int FuncNumber, FILE* f_out, int ret_value = UNDEF);
int ReduseRsp (Node* root);
int Hash (const char* str);
void Arithmetic_op (Node* root, int FuncNumber, FILE* f_out, int ret_value, int command);
void RedusePrecision (FILE* f_out, Node* elem, int ret_value = UNDEF);

int main () {

    FILE* f_in = fopen ("./resources/tree.txt", "r");
    assert (f_in);

    Node* root = {};
    root = GetTreeFromFile (root, f_in);
    fclose (f_in);

    FILE* f_asm = fopen ("./resources/ASMx86/experement.asm", "w");
    assert (f_asm);
    setbuf (f_asm, NULL);

    ProgramToASM (root, NullFunc, f_asm);
    fclose (f_asm);
    
    
    return 0;
}



void ProgramToASM (Node* root, int FuncNumber, FILE* f_out, int ret_value) {
    if (root) {
        int buf = 0;
        switch (root->type) {
            case START:
                fprintf (f_out, start_s);
                ProgramToASM (_R,  FuncNumber, f_out);
                fprintf (f_out, itoa_s);
                fprintf (f_out, atoi_s);
                fprintf(f_out, "\t\tSYMB_POINT equ %d\n", static_cast<int> (log10 (Precision)));
                break;
            case D:
                ProgramToASM (_R,  FuncNumber, f_out);
                ProgramToASM (_Lf, FuncNumber, f_out);
                break;
            case DEF:
                fprintf (f_out, "%s:\n"
                                "\t\tpush rbp\n"
                                "\t\tmov rbp, rsp\n"
                                "\t\tsub rsp, %d\n\n", _R->data, Bytes * static_cast<int> (_R->left->num));
                //POPargs      (_Lf, 1, f_out);
                ProgramToASM (_R,  static_cast<int> (root->right->num) - NullFunc, f_out);
                break;
            case FUNC:
                ProgramToASM (_R,  FuncNumber, f_out);
                break;
            case CALL:
                fprintf (f_out, "\n");
                ProgramToASM (_Lf, FuncNumber, f_out);
                
                fprintf (f_out, "\t\tcall %s\n", _R->data);
                fprintf (f_out, "\t\tadd rsp, %d\n", Bytes * ReduseRsp (_Lf));
                if (ret_value != RAX) {
                   fprintf (f_out, "\t\tmov %s, rax\n\n", reg_for_math[ret_value]); 
                }
                //ProgramToASM (_R,  FuncNumber, f_out);
                break;
            case COMMA:
                if (_R->type == NUM || _R->type == VAR) {
                    if (_R->type == NUM) fprintf (f_out, "\t\tpush qword %d\n", static_cast<int> (_R->num));
                    if (_R->type == VAR) fprintf (f_out, "\t\tpush qword [rbp%+d]\n", Bytes * static_cast<int> (_R->num));
                } else {
                    ProgramToASM (_R,  FuncNumber, f_out, RBX);
                    fprintf (f_out, "\t\tpush qword rbx\n");
                }
                ProgramToASM (_Lf, FuncNumber, f_out);
                break;
            case B:
                ProgramToASM (_R,  FuncNumber, f_out);
                break;
            case OP:
                ProgramToASM (_R,  FuncNumber, f_out);
                ProgramToASM (_Lf, FuncNumber, f_out);
                break;
            case ASSIGN:
                if (_R->type == NUM) {
                    fprintf (f_out, "\t\tmov qword [rbp%+d], %d\n", Bytes * static_cast<int> (_Lf->num), static_cast<int> (_R->num));
                } else if (_R->type == CALL) {
                    ProgramToASM (_R,  FuncNumber, f_out, RAX);
                    fprintf (f_out, "\t\tmov qword [rbp%+d], rax\n", Bytes * static_cast<int> (_Lf->num));
                } else {
                    ProgramToASM (_R,  FuncNumber, f_out, RBX);
                    fprintf (f_out, "\t\tmov qword [rbp%+d], rbx\n", Bytes * static_cast<int> (_Lf->num));
                }
                
                //fprintf (f_out, "%d\n", FuncNumber);
                break;
            case IF:

                buf = IfNumber;
                ProgramToASM (_Lf, FuncNumber, f_out);
                IfNumber++;
                ProgramToASM (_R,  FuncNumber, f_out);
                fprintf (f_out, "end_if%d:\n", buf);
                break;
            case EQUAL:
                ProgramToASM (_Lf, FuncNumber, f_out, RBX);
                ProgramToASM (_R,  FuncNumber, f_out, RCX);

                fprintf (f_out, "\t\tcmp rbx, rcx\n"
                                "\t\tjne end_if%d\n", IfNumber);
                break;
            case UNEQUAL:
                ProgramToASM (_Lf, FuncNumber, f_out, RBX);
                ProgramToASM (_R,  FuncNumber, f_out, RCX);
                fprintf (f_out, "\t\tcmp rbx, rcx\n"
                                "\t\tje end_if%d\n", IfNumber);
                break;
            case MORE:
                ProgramToASM (_R,  FuncNumber, f_out, RBX);
                ProgramToASM (_Lf, FuncNumber, f_out, RCX);

                fprintf (f_out, "\t\tcmp rbx, rcx\n"
                                "\t\tjg end_if%d\n", IfNumber);
                break;
            case SUM:
                Arithmetic_op (root, FuncNumber, f_out, ret_value, SUM);
                break;
            case SUB:
                ProgramToASM (_Lf, FuncNumber, f_out, ret_value);
                if (_R->type == NUM) {
                    fprintf (f_out, "\t\tsub %s, qword %d\n", reg_for_math[ret_value], Precision * static_cast<int> (_R->num));
                } else if (_R->type == VAR) {
                    fprintf (f_out, "\t\tsub %s, qword [rbp%+d]\n", reg_for_math[ret_value], Bytes * static_cast<int> (_R->num));
                } else {
                    ProgramToASM (_R, FuncNumber, f_out, ret_value + 1);
                    fprintf (f_out, "\t\tsub %s, %s\n", reg_for_math[ret_value], reg_for_math[ret_value + 1]);
                }
                break;
            case MUL:
                Arithmetic_op (root, FuncNumber, f_out, ret_value, MUL);
                break;
            case DIV:
                if (_R->type == NUM) {
                    ProgramToASM (_Lf, FuncNumber, f_out, RAX);
                    fprintf (f_out, "\t\tcqo\n");
                    fprintf (f_out, "\t\tidiv qword %d\n", Precision * static_cast<int> (_R->num));
                } else if (_R->type == VAR) {
                    RedusePrecision (f_out, _R);
                    ProgramToASM (_Lf, FuncNumber, f_out, RAX);
                    fprintf (f_out, "\t\tcqo\n");
                    fprintf (f_out, "\t\tidiv qword [rbp%+d]\n", Bytes * static_cast<int> (_R->num));
                } else {
                    ProgramToASM (_R, FuncNumber, f_out, ret_value + 1);
                    RedusePrecision (f_out, _R, ret_value + 1);
                    ProgramToASM (_Lf, FuncNumber, f_out, RAX);
                    fprintf (f_out, "\t\tcqo\n");
                    fprintf (f_out, "\t\tidiv %s\n", reg_for_math[ret_value + 1]);
                }
                if (ret_value != RAX) {
                    fprintf (f_out, "\t\tmov %s, rax\n", reg_for_math[ret_value]);
                }
                break;
            case RETURN:
                ProgramToASM (_R,  FuncNumber, f_out, RAX);
                fprintf (f_out, ret_s);
                break;
            case OUTPUT:
                ProgramToASM (_R,  FuncNumber, f_out, RBX);
                fprintf (f_out, output_s);
                break;
            case INPUT:
                fprintf (f_out, input_s);
                fprintf (f_out, "\t\timul rax, %d\n"
                                "\t\tmov qword [rbp%+d], rax\n\n", Precision, Bytes * static_cast<int> (_R->num));
                break;
            case SQRT:
                ProgramToASM (_R,  FuncNumber, f_out);
                fprintf (f_out, "\t\tSQRT\n");
                break;
            case BREAK:
                ProgramToASM (_R,  FuncNumber, f_out);
                fprintf (f_out, "\t\tBREAK\n");
                break;
            case DIFF:
                ProgramToASM (_R,  FuncNumber, f_out);
                fprintf (f_out, "\t\tDIFF\n");
                break;
            case VAR:
                if (ret_value != UNDEF) {
                    fprintf (f_out, "\t\tmov %s, qword [rbp%+d]\n", reg_for_math[ret_value], Bytes * static_cast<int> (root->num));    
                } 
                break;
            case NUM:
                if (ret_value != UNDEF) {
                    fprintf (f_out, "\t\tmov %s, qword %d\n", reg_for_math[ret_value], Precision * static_cast<int> (root->num));    
                } else {
                    //fprintf (f_out, "\t\tpush %lg\n", root->num);
                }
                break;
            default:
                printf ("\n! ERROR ! Неизвестный узел %s, тип: %d", root->data, root->type);
                break;
        }
    }
}
void RedusePrecision (FILE* f_out, Node* elem, int ret_value) {
    if (ret_value != UNDEF) {
        fprintf (f_out, "\n\t\tmov rax, %s\n"
                        "\t\tmov r15 , %d\n"
                        "\t\tcqo\n"
                        "\t\tidiv r15\n"
                        "\t\tmov qword %s, rax\n\n", reg_for_math[ret_value], Precision, reg_for_math[ret_value]);
    } else {
        if (elem->type == VAR) {
            int var_offset = static_cast<int> (elem->num);
            fprintf (f_out, "\n\t\tmov rax, qword [rbp%+d]\n"
                        "\t\tmov r15 , %d\n"
                        "\t\tcqo\n"
                        "\t\tidiv r15\n"
                        "\t\tmov qword [rbp%+d], rax\n\n", var_offset, Precision, var_offset);
        }
    }
}


void Arithmetic_op (Node* root, int FuncNumber, FILE* f_out, int ret_value, int command) {
    command -= SUM;
    if (_Lf->type == VAR || _Lf->type == NUM) {
        
        ProgramToASM (_R,  FuncNumber, f_out, ret_value);
        if (command == MUL - SUM) {
            RedusePrecision (f_out, _R, ret_value);
        }
        if (_Lf->type == VAR)
            fprintf (f_out, "\t\t%s %s, qword [rbp%+d]\n", arithmeic[command], reg_for_math[ret_value], Bytes * static_cast<int> (_Lf->num));
        if (_Lf->type == NUM)
            fprintf (f_out, "\t\t%s %s, qword %d\n", arithmeic[command], reg_for_math[ret_value], static_cast<int> (_Lf->num));

    } else if (_R->type == VAR || _R->type == NUM) {
        
        ProgramToASM (_Lf,  FuncNumber, f_out, ret_value);
        if (command == MUL - SUM) RedusePrecision (f_out, _Lf, ret_value);
        if (_R->type == VAR)
            fprintf (f_out, "\t\t%s %s, qword [rbp%+d]\n", arithmeic[command], reg_for_math[ret_value], Bytes * static_cast<int> (_R->num));
        if (_R->type == NUM)
            fprintf (f_out, "\t\t%s %s, qword %d\n", arithmeic[command], reg_for_math[ret_value], static_cast<int> (_R->num));
    
    } else {
    
        ProgramToASM (_Lf, FuncNumber, f_out, ret_value);
        if (command == MUL - SUM) RedusePrecision (f_out, _Lf, ret_value);
        ProgramToASM (_R,  FuncNumber, f_out, ret_value + 1);
        fprintf (f_out, "\t\t%s %s, %s\n", arithmeic[command], reg_for_math[ret_value], reg_for_math[ret_value + 1]);
    
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

#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include "Words.h"


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

void ProgramToASM (Node* root, int FuncNumber, FILE* f_out);
void POPargs (Node* root, int FuncNumber, FILE* f_out);
int Hash (const char* str);

int main () {

    FILE* f_in = fopen ("./resources/tree.txt", "r");
    assert (f_in);
    Node* root = GetTreeFromFile (root, f_in);
    fclose (f_in);

    FILE* f_asm = fopen ("./resources/asm_code.asm", "w");
    assert (f_asm);
    setbuf (f_asm, NULL);
    ProgramToASM (root, NullFunc, f_asm);
    fclose (f_asm);

    return 0;
}



void ProgramToASM (Node* root, int FuncNumber, FILE* f_out) {
    if (root) {
        int buf = 0;
        switch (root->type) {
            case START:
                fprintf (f_out, "CALL main\n"
                                "RET\n"
                                "\n");
                ProgramToASM(_R, FuncNumber, f_out);
                fprintf (f_out, "ENDING");
                break;
            case D:
                ProgramToASM(_R, FuncNumber, f_out);
                ProgramToASM(_Lf, FuncNumber, f_out);
                break;
            case DEF:
                fprintf (f_out, ":%s\n", root->right->data);
                POPargs (_Lf, (int) root->right->num - NullFunc, f_out);
                ProgramToASM(_R, (int) root->right->num - NullFunc, f_out);
                break;
            case FUNC:
                ProgramToASM(_R, FuncNumber, f_out);
                break;
            case CALL:
                ProgramToASM(_Lf, FuncNumber, f_out);
                fprintf (f_out, "PUSHR ax\n"
                                "PUSH %d\n"
                                "ADD\n"
                                "POP ax\n", ColVarsInOneFunc);
                fprintf (f_out, "CALL %s\n", _R->data);
                ProgramToASM(_R, FuncNumber, f_out);
                break;
            case COMMA:
                ProgramToASM(_R, FuncNumber, f_out);
                ProgramToASM(_Lf, FuncNumber, f_out);
                break;
            case B:
                ProgramToASM(_R, FuncNumber, f_out);
                break;
            case OP:
                ProgramToASM(_R, FuncNumber, f_out);
                ProgramToASM(_Lf, FuncNumber, f_out);
                break;
            case ASSIGN:
                ProgramToASM(_R, FuncNumber, f_out);
                fprintf (f_out, "POPRAM [ax+%d]\n", (int) root->left->num);
                //fprintf (f_out, "%d\n", FuncNumber);
                break;
            case IF:

                buf = IfNumber;
                ProgramToASM(_Lf, FuncNumber, f_out);
                IfNumber++;
                ProgramToASM(_R, FuncNumber, f_out);
                fprintf (f_out, ":end_if%d\n", buf);
                break;
            case EQUAL:
                ProgramToASM(_Lf, FuncNumber, f_out);
                ProgramToASM(_R, FuncNumber, f_out);
                fprintf (f_out, "JNE end_if%d\n", IfNumber);
                break;
            case UNEQUAL:
                ProgramToASM(_Lf, FuncNumber, f_out);
                ProgramToASM(_R, FuncNumber, f_out);
                fprintf (f_out, "JE end_if%d\n", IfNumber);
                break;
            case MORE:
                ProgramToASM(_R, FuncNumber, f_out);
                ProgramToASM(_Lf, FuncNumber, f_out);
                fprintf (f_out, "JA end_if%d\n", IfNumber);
                break;
            case SUM:
                ProgramToASM(_R, FuncNumber, f_out);
                ProgramToASM(_Lf, FuncNumber, f_out);
                fprintf (f_out, "ADD\n");
                break;
            case SUB:
                ProgramToASM(_R, FuncNumber, f_out);
                ProgramToASM(_Lf, FuncNumber, f_out);

                fprintf (f_out, "SUB\n");
                break;
            case MUL:
                ProgramToASM(_R, FuncNumber, f_out);
                ProgramToASM(_Lf, FuncNumber, f_out);
                fprintf (f_out, "MUL\n");
                break;
            case DIV:
                ProgramToASM(_Lf, FuncNumber, f_out);
                ProgramToASM(_R, FuncNumber, f_out);
                fprintf (f_out, "DIV\n");
                break;
            case RETURN:
                ProgramToASM(_R, FuncNumber, f_out);
                fprintf (f_out, "PUSH %d\n"
                                "PUSHR ax\n"
                                "SUB\n"
                                "POP ax\n", ColVarsInOneFunc);
                fprintf (f_out, "RET\n");
                break;
            case OUTPUT:
                ProgramToASM(_R, FuncNumber, f_out);
                fprintf (f_out, "OUT\n");
                break;
            case INPUT:
                fprintf (f_out, "IN\n");
                fprintf (f_out, "POPRAM [ax+%d]\n", (int) _R->num);
                break;
            case SQRT:
                ProgramToASM(_R, FuncNumber, f_out);
                fprintf (f_out, "SQRT\n");
            case BREAK:
                ProgramToASM(_R, FuncNumber, f_out);
                fprintf (f_out, "BREAK\n");
            case DIFF:
                ProgramToASM(_R, FuncNumber, f_out);
                fprintf (f_out, "DIFF\n");
                break;
            case VAR:
                fprintf (f_out, "PUSHRAM [ax+%d]\n", (int) root->num);
                break;
            case NUM:
                fprintf (f_out, "PUSH %lg\n", root->num);
                break;
            default:
                printf ("\n! ERROR ! Неизвестный узел %s, тип: %d", root->data, root->type);
                break;
        }
    }
}

void POPargs (Node* root, int FuncNumber, FILE* f_out) {
    if (root) {
        assert (root->type = COMMA);
        POPargs (_Lf, FuncNumber, f_out);
        fprintf (f_out, "POPRAM [ax+%d]\n", (int) _R->num);
    }
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

    for (char* p = (char*) str; *p != '\0'; p++)
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

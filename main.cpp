#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "Words.h"
#include <ctype.h>

#define _SUM(left, right) CreateNode (SUM, "+", left, right)
#define _SUB(left, right) CreateNode (SUB, "-", left, right)
#define _MUL(left, right) CreateNode (MUL, "*", left, right)
#define _DIV(left, right) CreateNode (DIV, "/", left, right)
#define _POW(left, right) CreateNode (POW, "^", left, right)
#define _VAR(word) CreateNode (VAR, word, nullptr, nullptr)
#define _KEYWORD(type) CreateNode (type, #type, nullptr, nullptr)
#define _NUM(num)   CreateNode (num)
#define _SIN(right) CreateNode (SIN, "sin", nullptr, right)
#define _COS(right) CreateNode (COS, "cos", nullptr, right)
#define _TG(right)  CreateNode (TG,  "tg",  nullptr, right)
#define _CTG(right) CreateNode (CTG, "ctg", nullptr, right)
#define _ARCTG(right) CreateNode (ARCTG, "arctg", nullptr, right)
#define _LN(right)  CreateNode (LN,  "ln",  nullptr, right)
#define _SH(right)  CreateNode (SH,  "sh",  nullptr, right)
#define _CH(right)  CreateNode (CH,  "ch",  nullptr, right)
#define _TH(right)  CreateNode (TH,  "th",  nullptr, right)
#define _CTH(right) CreateNode (CTH, "cth", nullptr, right)
#define cL CopyNode (node->left)
#define cR CopyNode (node->right)
#define dL DifNode  (node->left)
#define dR DifNode  (node->right)
#define _Lf root->left
#define _R  root->right
#define _R_num_0  ((0 < _R->num  &&_R->num  < Precision) || (0 > _R->num  &&_R->num  > -Precision))
#define _Lf_num_0 ((0 < _Lf->num &&_Lf->num < Precision) || (0 > _Lf->num &&_Lf->num > -Precision))
#define _R_num_1  (1.0 - Precision < _R->num  &&_R->num  < 1.0 + Precision)
#define _Lf_num_1 (1.0 - Precision < _Lf->num &&_Lf->num < 1.0 + Precision)
#define NT Nods[ind]->type
#define NewEl(TYPE, symbl) \
case symbl:                                                       \
    Nodes[i] = CreateNode (TYPE, #symbl, nullptr, nullptr);       \
    printf ("%s %d\n", Nodes[i]->data, Nodes[i]->type);                       \
    i++;                                                           \
    s++;                                                           \
    break;                                                         \


#define _NewEl(type)                                       \
else if ( strcmp (#type, data) == 0)                                      \
    root =  CreateNode (type, #type, nullptr, nullptr);    \

#define _NewTerm(dat, type)   \
else if (strcmp (dat, data) == 0)                   \
    root = CreateNode (type, data, nullptr, nullptr);      \


struct Node
{
    char* data;
    double num;
    Node* left;
    Node* right;
    int type;
};


const char* s = "";
Node** Nods = nullptr;
constexpr int WordSize = 40;
constexpr int ColNodes = 350;
constexpr int ProgramSize = 1900;
constexpr int DataSize = 50;
constexpr int VarNum = 40;
constexpr int FuncNum = 30;
constexpr double Precision = 0.00000001;
//constexpr int NullFunc = FUNCCOL - COL_WORDS - 1;
//constexpr int ColVarsInOneFunc = 30;


int ind = 0;
double VarNumber = 0;

struct IdsArray
{
    int* data;
    int free;
};


Node* Prog (Node** Nodes);
Node* Declare ();
Node* VarlistDef ();
Node* VarlistE ();
Node* Call ();
Node* Func ();
Node* Operator ();
Node* Break  ();
Node* Input  ();
Node* Output ();
Node* Assign ();
Node* If ();
Node* While  ();
Node* Return ();
Node* Cond   ();
Node* Block  ();

Node* GetE ();
Node* GetT ();
Node* GetStep ();
Node* GetP ();
Node* GetF ();
Node* GetN ();


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

/*! Функция, копирущая узел
*
*	@param [in] root Указатель на узел
*
*	@return Указатель на копию
*
*/
Node* CopyNode (Node* root);

/*! Функция дифференцирования дерева
*
*	@param [in] node Корень дерева
*
*	@return Указатель на продифференцированное дерево или nullptr в случае ошибки
*
*/
Node* DifNode (const Node* node);
void DelNode (Node* node);
void DeleteTree (Node* root);
void PrintNods (Node* node, FILE* f_out);
void NodePrint (Node* node, FILE* f_out);
void TreePrint (Node* root, FILE* f_out);
void SaveTree (Node* node, int RootType, FILE* f_sav);
void TreeToLaTex (Node* root, Node* d_root, FILE* f_tex);
void Simplification (Node* root);
void CopyTo (Node* root, Node* NewNode);
Node* NDifNode (Node* root, int number);
void VarToNum (Node* root, double num);
int MaklorenElement (Node* root, int num, FILE* f_out);
void MaklorenSeries (Node* root, int num, FILE* f_out);
void PrintMaclorenElement (int num, Node* d_root, FILE* f_out);
void DropSpace ();
Node** Tocens (IdsArray* Ids, IdsArray* IdsFunc, IdsArray* IdsParam, int* KeyWords);
void ReadProgramFromFile (FILE* f_in);
int Hash (const char* str);
int* KeyWordsArray ();
IdsArray* IdArrayCostruct (IdsArray* Ids);
void IdArrayDistruct (IdsArray* Ids);
void IdFuncArrayInit (IdsArray* Ids);
void ClearId (IdsArray* Ids);

int ElementIsInArr (IdsArray* Ids, const char* var);
int ElementIsInArr (IdsArray* Ids, int hash);

int KeyWordNum (const char* word, int* KeyWordsArr);
int KeyWordNum (int hash, int* KeyWordsArr);

Node* NewFuncOrKeyWordNode (const char* word, IdsArray* IdArr, int* KeyWords, int& sign);
Node* NewVarOrKeyWordNode (const char* word, IdsArray* VarArray, IdsArray* IdsParam, int* KeyWords, int& sign);

int AddNewEL (IdsArray* Ids, const char* var);
int AddNewEL (IdsArray* Ids, int hash);

void SaveTreeToFile (Node* root, FILE* f_sav);
Node* GetTreeFromFile (Node* root, FILE* f_in);

Node* MaklorenElement (Node* root, int num, int* SignEl);

inline bool float_is_same (double a, double b) {
    return (b - Precision < a  && a  < b + Precision);
}

int main () {

    FILE* f_in = fopen ("./resources/example.txt", "r");
    FILE* f_out = fopen ("./resources/output.dot", "w");
    
    assert (f_in);
    assert (f_out);

    setbuf (stdout, NULL);


    ReadProgramFromFile (f_in);
    IdsArray* Ids = nullptr;
    Ids = IdArrayCostruct (Ids);
    IdsArray* IdsFunc = nullptr;
    IdsFunc = IdArrayCostruct (IdsFunc);
    IdsArray* IdsParams = nullptr;
    IdsParams = IdArrayCostruct (IdsParams);
    IdFuncArrayInit (IdsFunc);
    int* KeyWordsArr = KeyWordsArray ();
    Node** Nodes = Tocens (Ids, IdsFunc, IdsParams, KeyWordsArr);

    Node* root = Prog (Nodes);
    Simplification (root);
    TreePrint (root, f_out);

    fclose (f_out);

    FILE* f_sav = fopen ("./resources/tree.txt", "w");
    setbuf (f_sav, NULL);
    SaveTreeToFile (root, f_sav);
    fclose (f_sav);

    // FILE* f_asm = fopen ("./resources/asm_code.asm", "w");
    // setbuf (f_asm, NULL);
    // ProgramToASM (root, NullFunc, f_asm);
    // fclose (f_asm);

    IdArrayDistruct (Ids);
    IdArrayDistruct (IdsFunc);
    IdArrayDistruct (IdsParams);
    DeleteTree (root);
    free (KeyWordsArr);
    free (Nodes);

    fclose (f_in);
    return 0;
}

Node* Prog (Node** Nodes) {

    Nods = Nodes;
    Node* val = nullptr;
    assert (NT == START);
    val = Nods[ind];
    ind++;
    if (NT != END) {
        val->right = Declare();
    }

    assert (NT == END);

    return val;
}

Node* Declare () {
    Node* val = CreateNode (D, "D", nullptr, nullptr);
    val->right = Func ();
    if (NT != END) {
        val->left = Declare();
    }
    return val;
}

Node* Func () {
    assert (NT == DEF);
    Node* val = Nods[ind];
    ind++;

    assert (NT == FUNC);
    val->right = Nods[ind];
    ind++;
    assert (NT == SKOBKA1);
    ind++;
    if (NT == VAR)
        val->left = VarlistDef();
    assert (NT == SKOBKA2);
    ind++;
    ind++;
    VarNumber = 0;
    val->right->right = Block ();
    val->right->left = _NUM (-VarNumber);

    return val;
}

Node* VarlistDef () {
    Node* val = CreateNode (COMMA, ",", nullptr, Nods[ind]);
    ind++;
    if (NT == COMMA) {
        ind++;
        assert (NT == VAR);
        val->left = VarlistDef();
    }
    return val;
}

Node* VarlistE () {
    Node* val = CreateNode (COMMA, ",", nullptr, GetE ());

    if (NT == COMMA) {
        ind++;
        val->left = VarlistE ();
    }
    return val;
}

Node* Call () {
    assert (NT == FUNC);
    Node* val = CreateNode (CALL, "CALL", nullptr, Nods[ind]);
    ind++;
    assert (NT == SKOBKA1);
    ind++;
    if (NT != SKOBKA2) {
        val->left = VarlistE ();
    }
    assert (NT == SKOBKA2);
    ind++;
    return val;
}

Node* Block () {
    Node* val = CreateNode (B, "B", nullptr, nullptr);
    assert (NT == BLOCK_ST);
    ind++;
    if (NT != BLOCK_END) {
        val->right = Operator ();
    }
    assert (NT == BLOCK_END);
    ind++;
    return val;
}

Node* Operator () {
    Node* val = CreateNode (OP, "OP", nullptr, nullptr);
    switch (NT) {
        case VAR:
            val->right = Assign ();
            break;
        case IF:
            val->right = If ();
            break;
        case WHILE:
            val->right = While ();
            break;
        case RETURN:
            val->right = Return ();
            break;
        case INPUT:
            val->right = Input ();
            break;
        case OUTPUT:
            val->right = Output ();
            break;
        case BREAK:
            val->right = Break ();
            break;
        case FUNC:
            val->right = Call ();
            break;
        default:
            printf ("! ERROR ! Unknown Operator %s  type: %d\n", Nods[ind]->data, Nods[ind]->type);
    }
    if (NT != BLOCK_END) {
        val->left = Operator ();
    }
    return val;
}

Node* Input () {
    assert (NT == INPUT);
    Node* val = Nods[ind];
    ind++;
    assert (NT == SKOBKA1);
    ind++;
    assert (NT == VAR);
    val->right = Nods[ind];
    ind++;
    assert (NT = SKOBKA2);
    ind++;
    return val;
}

Node* Break () {
    assert (NT == BREAK);
    Node* val = Nods[ind];
    ind++;
    assert (NT == SKOBKA1);
    ind++;
    val->right = GetE ();
    assert (NT = SKOBKA2);
    ind++;
    return val;
}

Node* Output () {
    assert (NT == OUTPUT);
    Node* val = Nods[ind];
    ind++;
    assert (NT == SKOBKA1);
    ind++;
    val->right = GetE ();
    assert (NT = SKOBKA2);
    ind++;
    return val;
}

Node* Assign () {
    assert (NT == VAR);
    if (Nods[ind]->num < VarNumber) VarNumber = Nods[ind]->num;
    ind++;
    Nods[ind]->left = Nods[ind - 1];
    Node* val =  Nods[ind];
    ind++;

    val->right = GetE ();
    assert (NT == COMMA_POINT);
    ind++;

    return val;
}

Node* If () {
    assert (NT == IF);
    Node* val = Nods[ind];
    ind++;
    assert (NT == SKOBKA1);
    ind++;
    val->left = Cond ();
    assert (NT == SKOBKA2);
    ind++;
    val->right = Block ();
    return val;
}

Node* While () {
    assert (NT == WHILE);
    Node* val = Nods[ind];
    ind++;
    assert (NT == SKOBKA1);
    ind++;
    val->left = Cond ();
    assert (NT == SKOBKA2);
    ind++;
    val->right = Block ();
    return val;
}

Node* Return () {
    assert (NT == RETURN);
    Node* val = Nods[ind];
    ind++;
    val->right = GetE ();
    assert (NT == COMMA_POINT);
    ind++;
    return val;
}

Node* Cond () {
    Node* val1 = GetE ();
    Node* val = Nods[ind];//CreateNode (NT, Words[NT], val1, nullptr);
    val->left = val1;
    ind++;
    Node* val2 = GetE ();
    val->right = val2;

    return val;
}

Node* GetE () {
    Node* val = nullptr;
    val = GetT ();
    while (NT == SUM || NT == SUB) {
        int type = NT;
        ind++;
        Node* val2 = GetT ();
        if (type == SUM) {
            val = _SUM (val, val2);
        }
        else
        {
            if (val == nullptr) val = _NUM (0);
            val = _SUB (val, val2);
        }

    }
    return val;
}

Node* GetT () {
    Node* val = nullptr;
    val = GetStep ();
    //val = GetP ();
    while (NT == MUL || NT == DIV) {
        int type = NT;
        ind++;
        Node* val2 = GetStep ();
        //Node* val2 = GetP ();
        if (type == MUL) {
            val = _MUL (val, val2);
            //val *= val2;
        }
        else
            val = _DIV (val, val2);
        //val /= val2;
    }
    return val;
}

Node* GetStep () {
    Node* val = nullptr;
    val = GetP ();
    printf ("!!! %s  type = %d\n", Nods[ind]->data, NT);
    while (NT == POW) {
        ind++;
        Node* val2 = GetP ();
        val = _POW (val, val2);
    }

    return val;
}

Node* GetP () {
    Node* val = nullptr;
    if (NT == SKOBKA1) {
        ind++;
        val = GetE ();
        if (NT != SKOBKA2) printf ("EEEEEEEEEEEEE %s", Nods[ind]->data);
        assert (NT == SKOBKA2);
       
        ind++;
        return val;
    }
    else if (NT == VAR) {
        val = Nods[ind];
        printf ("$$$$$ VarNumber %lf , var = %s   val->num = %lf\n", VarNumber, val->data, val->num);
        if (val->num < VarNumber) VarNumber = val->num;
        ind++;
        return val;
    }
    else if (NT == NUM)
        return GetN ();
    else if (NT == FUNC)
        return Call ();
    else
       return GetF ();

}

Node* GetF () {

    Node* val = nullptr;
    if (NT == SIN) {
        val = Nods[ind];
        ind++;
        val->right =  GetP ();
        return val;
    }

    if (NT == COS) {
        val = Nods[ind];
        ind++;
        val->right =  GetP ();
        return val;
    }

    if (NT == TG) {
        val = Nods[ind];
        ind++;
        val->right =  GetP ();
        return val;
    }

    if (NT == CTG) {
        val = Nods[ind];
        ind++;
        val->right =  GetP ();
        return val;
    }

    if (NT == LN) {
        val = Nods[ind];
        ind++;
        val->right =  GetP ();
        return val;
    }

    if (NT == ARCTG) {
        val = Nods[ind];
        ind++;
        val->right =  GetP ();
        return val;
    }

    if (NT == SH) {
        val = Nods[ind];
        ind++;
        val->right =  GetP ();
        return val;
    }

    if (NT == CH) {
        val = Nods[ind];
        ind++;
        val->right =  GetP ();
        return val;
    }

    if (NT == TH) {
        val = Nods[ind];
        ind++;
        val->right =  GetP ();
        return val;
    }

    if (NT == CTH) {
        val = Nods[ind];
        ind++;
        val->right =  GetP ();
        return val;
    }

    if (NT == SQRT) {
        val = Nods[ind];
        ind++;
        val->right =  GetP ();
        return val;
    }

    if (NT == DIFF) {
        val = Nods[ind];
        ind++;
        val->right =  GetP ();
        return val;
    }


//functions

    return val;
}

Node* GetN () {
    Node* res = Nods[ind];
    ind++;
    return res;
}

void SaveTreeToFile (Node* root, FILE* f_sav) {
    if (root) {
        fprintf (f_sav, "(");
        //free (malloc (100));
        if (root->type == NUM) fprintf (f_sav, "%lg", root->num);
        else if (root->type == VAR) {
            fprintf (f_sav, "@%lg%s", root->num, root->data);
        }
        else
            fprintf (f_sav, "%s", root->data);
        SaveTreeToFile (root->left, f_sav);
        SaveTreeToFile (root->right, f_sav);
        fprintf(f_sav, ")");
    } else {
        fprintf (f_sav, "()");
    }
}

void IdArrayDistruct (IdsArray* Ids) {
    free (Ids->data);
    free (Ids);
}

void ReadProgramFromFile (FILE* f_in) {
    int offset = 0;
    unsigned long long CountRead = 1;
    char* buf = (char*) calloc (ProgramSize, sizeof (char));
    while (CountRead > 0) {
        CountRead = fread (buf + offset, sizeof(char), ProgramSize, f_in);
    }
    s = buf;
}

int* KeyWordsArray () {
    int* KeyWords = (int*) calloc (COL_WORDS, sizeof (int));
    for (int i = 0; i < COL_WORDS; i++) {
        KeyWords[i] = Hash (Words[i]);
        //printf ("@ %s  %d\n", Words[i], KeyWords[i]);
    }

    return KeyWords;
}

IdsArray* IdArrayCostruct (IdsArray* Ids) {
    Ids = (IdsArray*) calloc (1, sizeof (IdsArray));
    Ids->data = (int*) calloc (VarNum, sizeof (int));
    Ids->free = 1;
    return Ids;
}

void ClearId (IdsArray* Ids) {
    for (int i = 0; i < VarNum; ++i) {
        Ids->data[i] = 0;
    }
    Ids->free = 1;
}

void IdFuncArrayInit (IdsArray* Ids) {
    for (int i = COL_WORDS + 1; i < FUNCCOL; i++) {
        Ids->data[Ids->free] = Hash (Words[i]);
        Ids->free++;
    }
}

int ElementIsInArr (IdsArray* Ids, const char* var) {

    int hash = Hash (var);
    for (int i = 0; i < Ids->free; i++) {
        if (hash == Ids->data[i]) {
            return i;
        }
    }

    return -1;
}

int ElementIsInArr (IdsArray* Ids, int hash) {
    for (int i = 0; i < Ids->free; i++) {
        if (hash == Ids->data[i]) {
            return i;
        }
    }

    return -1;
}

int AddNewEL (IdsArray* Ids, const char* var) {
    Ids->data[Ids->free] = Hash (var);
    Ids->free++;

    return Ids->free - 1;
}

int AddNewEL (IdsArray* Ids, int hash) {
    Ids->data[Ids->free] = hash;
    Ids->free++;

    return Ids->free - 1;
}

int Hash (const char* str) {
    int hash = 0;

    for (char* p = const_cast<char*> (str); *p != '\0'; p++)
        hash = 3 * hash + (*p >> 3 | 1233) + *p;

    return hash;
}

int KeyWordNum (const char* word, int* KeyWordsArr) {
    int hash = Hash (word);
    for (int i = 0; i < COL_WORDS; i++) {
        if (hash == KeyWordsArr[i]) return i;
    }

    return -1;
}

int KeyWordNum (int hash, int* KeyWordsArr) {
    for (int i = 0; i < COL_WORDS; i++) {
        if (hash == KeyWordsArr[i]) return i;
    }

    return -1;
}

Node* NewFuncOrKeyWordNode (const char* word, IdsArray* FuncArray, int* KeyWords, int& sign) {
    int hash = Hash (word);
    int num = KeyWordNum (hash, KeyWords);
    if (num != -1) {
        switch (num) {
            case START:
                return _KEYWORD (START);
            case END:
                return _KEYWORD (END);
            case IF:
                return _KEYWORD (IF);
            case WHILE:
                return _KEYWORD (WHILE);
            case BLOCK_ST:
                return _KEYWORD (BLOCK_ST);
            case BLOCK_END:
                return _KEYWORD (BLOCK_END);
            case DBLPOINT:
                printf ("&&&&&&&&&&&&&&&&&&&&&&&&\n");
                sign *= -1;
                return _KEYWORD (DBLPOINT);
            case SKOBKA1:
                return _KEYWORD (SKOBKA1);
            case SKOBKA2:
                return _KEYWORD (SKOBKA2);
            case ASSIGN:
                return _KEYWORD (ASSIGN);
            case EQUAL:
                return _KEYWORD (EQUAL);
            case UNEQUAL:
                return _KEYWORD (UNEQUAL);
            case MORE:
                return _KEYWORD (MORE);
            case COMMA_POINT:
                return _KEYWORD (COMMA_POINT);
            case RETURN:
                return _KEYWORD (RETURN);
            case INPUT:
                return _KEYWORD (INPUT);
            case OUTPUT:
                return _KEYWORD (OUTPUT);
            case BREAK:
                return _KEYWORD (BREAK);
            default:
                printf ("ERROR: Undefined keyword");
                return nullptr;
        }
    } else {
        num = ElementIsInArr (FuncArray, hash) + COL_WORDS + 1;
        printf ("\t\t\t\t hash = %d\n", hash);
        if (num  != COL_WORDS) {
            switch (num - 1) {
                case SIN:
                    return _SIN (nullptr);
                case COS:
                    return _COS (nullptr);
                case TG:
                    return _TG (nullptr);
                case CTG:
                    return _CTG (nullptr);
                case ARCTG:
                    return _ARCTG (nullptr);
                case LN:
                    return _LN (nullptr);
                case SH:
                    return _SH (nullptr);
                case CH:
                    return _CH (nullptr);
                case TH:
                    return _TH (nullptr);
                case CTH:
                    return _CTH (nullptr);
                case SQRT:
                    return CreateNode (SQRT, word, nullptr, nullptr);
                case DIFF:
                    printf ("AAAAAAAAAAAAAAAAAA\n");
                    //printf ("%d\n", Hash (Words[30]));
                    return CreateNode (DIFF, word, nullptr, nullptr);
                default:
                    printf ("ERROR: Undefined function ot operator\n");
                    break;
            }
            //printf ("^ %lg\n", (double) num);
            return CreateNode (FUNC, word, nullptr, nullptr, (double) (num - COL_WORDS - 1));
        }
        else
        {
            num = AddNewEL (FuncArray, hash);
            //printf ("^^^^ %lg\n", (double) num);
            return CreateNode (FUNC, word, nullptr, nullptr, (double) num);
        }
    }
    //printf ("^^^ %lg\n", (double) num);
    return CreateNode (FUNC, word, nullptr, nullptr, (double) num);
}

void DropSpace () {
    while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r') {
        s++;
    }
}

Node* NewVarOrKeyWordNode (const char* word, IdsArray* VarArray, IdsArray* IdsParam, int* KeyWords, int& sign) {
    int hash = Hash (word);
    int num = KeyWordNum (hash, KeyWords);
    if (num != -1) {
        switch (num) {
            case START:
                return _KEYWORD (START);
            case END:
                return _KEYWORD (END);
            case IF:
                return _KEYWORD (IF);
            case WHILE:
                return _KEYWORD (WHILE);
            case BLOCK_ST:
                return _KEYWORD (BLOCK_ST);
            case BLOCK_END:
                return _KEYWORD (BLOCK_END);
            case SKOBKA1:
                return _KEYWORD (SKOBKA1);
            case SKOBKA2:
                return _KEYWORD (SKOBKA2);
            case ASSIGN:
                return _KEYWORD (ASSIGN);
            case DEF:
                sign *= -1;
                printf ("DEF sign = %d\n", sign);
                ClearId (VarArray);
                ClearId (IdsParam);
                return _KEYWORD (DEF);
            case EQUAL:
                return _KEYWORD (EQUAL);
            case UNEQUAL:
                return _KEYWORD (UNEQUAL);
            case MORE:
                return _KEYWORD (MORE);
            case RETURN:
                return _KEYWORD (RETURN);
            case INPUT:
                return _KEYWORD (INPUT);
            case OUTPUT:
                return _KEYWORD (OUTPUT);
            case BREAK:
                return _KEYWORD (BREAK);
            default:
                printf ("ERROR: Can't do node, undifined operator\n");
                return nullptr;
        }
    } else {
        num = ElementIsInArr (IdsParam, hash);
        if (num == -1 && sign < 0) {
            num = ElementIsInArr (VarArray, hash);
            if (num == -1)
            {
                num = AddNewEL (VarArray, hash);
            }
        } else if (num != -1 && sign < 0) {
            num++;
            num *= -1;
        } else if (sign > 0) {
            num = AddNewEL (IdsParam, hash);
            num++;
        }
    }
    return CreateNode (VAR, word, nullptr, nullptr, (double) num * sign);
}

Node** Tocens (IdsArray* Ids, IdsArray* IdsFunc, IdsArray* IdsParam, int* KeyWords) {
    int n = 0;
    Node** Nodes = (Node**) calloc (ColNodes, sizeof (Node*));

    int i = 0;

    double num = 0;
    int sign = -1;
    char* word = (char*) calloc (WordSize, sizeof (char));
    while (*s != '\0') {
        if (isalpha (*s)) {
            sscanf (s, "%[^()\n\t\r=^+-*/><!&|;, ]%n", word, &n);
            s += n;
            DropSpace();
            if (*s == '(') {
                Nodes[i] = NewFuncOrKeyWordNode (word, IdsFunc, KeyWords, sign);
            }
            else
                Nodes[i] = NewVarOrKeyWordNode (word, Ids, IdsParam, KeyWords, sign);
            printf ("%s data = \'%s\' type = %d   num = %lg\n", word, Nodes[i]->data, Nodes[i]->type, Nodes[i]->num);
            i++;
            //printf ("********* %d  %d  %d********\n", KeyWords[10], KeyWords[11], Hash ("def"));
            //printf ("%s\n", word);
        }
        else if (isdigit (*s)) {
            sscanf (s, "%lg%n", &num, &n);
            //printf ("%d", n);
            s += n;
            Nodes[i] = _NUM (num);
            printf ("%lf\n", Nodes[i]->num);
            i++;
        }
        else {
            switch (*s) {
                case ' ':
                    DropSpace ();
                    break;
                case '\n':
                    DropSpace();
                    break;
                case '\r':
                    DropSpace();
                    break;
                NewEl (BLOCK_ST, '{')
                NewEl (BLOCK_END, '}')
                NewEl (SKOBKA1, '(')
                NewEl (SKOBKA2, ')')
                NewEl (SUM, '+')
                NewEl (SUB, '-')
                NewEl (MUL, '*')
                NewEl (DIV, '/')
                NewEl (POW, '^')
                NewEl (ASSIGN, '=')
                NewEl (MORE, '>')
                NewEl (COMMA_POINT, ';')
                NewEl (COMMA, ',')
                case ':':                                                       
                    Nodes[i] = CreateNode (DBLPOINT, ":", nullptr, nullptr);       
                    printf ("%s %d\n", Nodes[i]->data, Nodes[i]->type);                       
                    i++;                                                           
                    s++;
                    sign *= -1;
                    printf ("sign = %d\n", sign);
                    ClearId (Ids);                                                       
                    break;                                                         
                default:
                    printf ("Undefined symbol %c\n", *s);
            }

        }
    }

    return Nodes;
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

void Simplification (Node* root) {
    if (root) {
        Node* NewNode = nullptr;
        if (_Lf && _R) {
            Simplification (_Lf);
            Simplification (_R);
            if (_Lf->type == NUM && _R->type == NUM) {
                switch (root->type) {
                    case SUM:
                        NewNode = _NUM (_Lf->num + _R->num);
                        CopyTo (root, NewNode);
                        break;
                    case SUB:
                        NewNode = _NUM (_Lf->num - _R->num);
                        CopyTo (root, NewNode);
                        break;
                    case MUL:
                        NewNode = _NUM (_Lf->num * _R->num);
                        CopyTo (root, NewNode);
                        break;
                    case DIV:
                        if ((0 < _R->num &&_R->num < Precision) || (0 > _R->num &&_R->num > -Precision)) {
                            NewNode = _NUM (_Lf->num / _R->num);
                            CopyTo (root, NewNode);
                        }
                        break;
                    case POW:
                        //assert (_Lf->num == 0);
                        NewNode = _NUM (pow(_Lf->num, _R->num));
                        CopyTo(root, NewNode);
                        break;
                    default:
                        break;
                }
            }

            switch (root->type) {
                case MUL:
                    if ((_Lf->type == NUM && _Lf_num_0) || (_R->type == NUM && _R_num_0)) {
                        NewNode = _NUM (0);
                        CopyTo (root, NewNode);
                    } else if  (_Lf->type == NUM && _Lf_num_1) {
                        CopyTo (root, _R);
                    } else if (_R->type == NUM && _R_num_1) {
                        CopyTo (root, _Lf);
                    }
//                    else if (_Lf->type == _R->type && ((_Lf->type == VAR && _Lf->num == _R->num) || ( COL_WORDS < _Lf->type && _Lf->type < FUNCCOL))) {
//                        NewNode = _POW (_Lf, _NUM(2));
//                        CopyTo (root, NewNode);
//                    }
                    break;
                case DIV:
                    if (_Lf->type == NUM && _Lf_num_0) {
                        NewNode = _NUM (0);
                        CopyTo (root, NewNode);
                    } else if (_R->type == NUM &&_R_num_1) {
                        CopyTo (root, _Lf);
                    }
                    break;
                case SUM:
                    if (_Lf->type == NUM && _Lf_num_0) {
                        CopyTo (root, _R);
                    } else if (_R->type == NUM && _R_num_0) {
                        CopyTo (root, _Lf);
                    }
                    break;
                case SUB:
                    if (_Lf->type == NUM && _Lf_num_0) {
                        NewNode = _MUL (_NUM (-1), _R);
                        CopyTo (root, NewNode);
                    } else if (_R->type == NUM && _R_num_0) {
                        CopyTo (root, _Lf);
                    }
                    break;
                case POW:
                    if (_R->type == NUM && _R_num_0) {
                        NewNode = _NUM (1);
                        CopyTo (root, NewNode);
                    } else if (_Lf->type == NUM && _Lf_num_1) {
                        NewNode = _NUM (1);
                        CopyTo (root, NewNode);
                    } else if (_R->type == NUM && _R_num_1) {
                        CopyTo (root, _Lf);
                    } else if (_Lf->type == POW) {
                        NewNode = _POW (_Lf->left, _NUM (_Lf->right->num * _R->num));
                        CopyTo (root, NewNode);
                    }
                    break;
                default:
                    break;
            }
        } else if (_R) {
            Simplification(_R);
            if ( _R->type == NUM) {
                switch (root->type) {
                    case SIN:
                        NewNode = _NUM (sin(_R->num));
                        CopyTo(root, NewNode);
                        break;
                    case COS:
                        NewNode = _NUM (cos(_R->num));
                        CopyTo(root, NewNode);
                        break;
                    case TG:
                        NewNode = _NUM (tan(_R->num));
                        CopyTo(root, NewNode);
                        break;
                    case CTG:
                        NewNode = _NUM (1 / tan(_R->num));
                        CopyTo(root, NewNode);
                        break;
                    case SH:
                        NewNode = _NUM (sinh(_R->num));
                        CopyTo(root, NewNode);
                        break;
                    case CH:
                        NewNode = _NUM (cosh(_R->num));
                        CopyTo(root, NewNode);
                        break;
                    case TH:
                        NewNode = _NUM (tanh(_R->num));
                        CopyTo(root, NewNode);
                        break;
                    case CTH:
                        NewNode = _NUM (1 / tanh(_R->num));
                        CopyTo(root, NewNode);
                        break;
                    case ARCTG:
                        NewNode = _NUM (atan(_R->num));
                        CopyTo(root, NewNode);
                        break;
                    case LN:
                        NewNode = _NUM (log(_R->num));
                        CopyTo(root, NewNode);
                        break;
                    default:
                        break;
                }
            }
            else if (root->type == DIFF) {
                NewNode = DifNode (_R);
                Simplification (NewNode);
                CopyTo (root, NewNode);
            }
        } else if (_Lf) {
            Simplification (_Lf);
        }
    }
}

void CopyTo (Node* root, Node* NewNode) {

    _Lf = NewNode->left;
    _R = NewNode->right;
    root->num = NewNode->num;
    root->type = NewNode->type;
    root->data = NewNode->data;
}

void VarToNum (Node* root, double num) {
    if (root) {
        VarToNum (_Lf, num);
        VarToNum (_R, num);
        if (root->type == VAR) {
            root->type = NUM;
            root->num = num;
        }
    }
}

Node* MaklorenElement (Node* root, int num, int* SignEl) {

    Node* root_copy = CopyNode (root);
    Node* d_root = NDifNode (root_copy, num);

    if (num != 0) {
        VarToNum (d_root, 0);
        Simplification (d_root);

        if (d_root->type == NUM && float_is_same (d_root->num, 0)) {
            DeleteTree (root_copy);
            DeleteTree (d_root);
            *SignEl = 0;
            return nullptr;
        }
        else if (d_root->num < 0) {
            d_root->num *= -1;
            *SignEl = -1;
            //return nullptr;
        } else {
            *SignEl = 1;
        }

        //PrintMaclorenElement (num, d_root, f_out);
        DeleteTree (d_root);
    }
    else
    {
        VarToNum (root_copy, 0);
        Simplification (root_copy);

        if (float_is_same (root_copy->num, 0)) {
            //DeleteTree (root_copy);
            *SignEl = 0;
        } else if (root_copy->num < 0) {
            root_copy->num *= -1;
            *SignEl = -1;
        } else {
            *SignEl = 1;
        }
//        if (abs (root_copy->num  - (int) root_copy->num) < 0.00001)
//            fprintf (f_out, "%d", (int) root_copy->num);
//        else
//            fprintf (f_out, "%.2lf", root_copy->num);
        //PrintMaclorenElement (num, d_root, f_out);
    }
    DeleteTree (root_copy);
    return d_root;
}

void PrintMaclorenElement (int num, Node* d_root, FILE* f_out) {
    if ((d_root->type != NUM || !float_is_same (d_root->num, 0)) && num != 0) {
        fprintf(f_out, "\\frac {");
        SaveTree (d_root, 0, f_out);
        fprintf (f_out, " \\cdot x^{%d}} {%d!} ", num, num);
    }
    else if (num == 0 && !float_is_same (d_root->num, 0)) {
        fprintf (f_out, "%lg", d_root->num);
    }
}

void MaklorenSeries (Node* root, int num, FILE* f_out) {
    fprintf (f_out, "{\\Large \\begin{center}\n"
                    "\\begin{math}\n"
                    "f(x)=");
    int SignElement = 0;
    bool IsFirst = true;
    Node* d_root;
    for (int i = 0; i < num + 1; i++) {
        d_root = MaklorenElement (root, i, &SignElement);
        if (i == 0 && SignElement == 0) IsFirst = false;
        switch (SignElement) {
            case 0:
                break;
            case 1:
                if (i != 0 && !(!IsFirst && i == 1 )) fprintf (f_out, "+");
                PrintMaclorenElement (i, d_root,f_out);
                break;
            case -1:
                if (i != 0 && !(!IsFirst && i == 1 )) fprintf (f_out, "-");
                PrintMaclorenElement (i, d_root, f_out);
                break;
            default:
                break;
        }

    }
    fprintf (f_out, "+o(x^{%d})\n", num);
    fprintf (f_out, "\\end{math}\n"
                    "\\end{center}}\n");
}

Node* NDifNode (Node* root, int number) {

    Node* d_root = root;

    for (int i = 0; i < number; i++) {
        Simplification (d_root);
        d_root = DifNode (d_root);
    }

    Simplification (d_root);
    return d_root;
}

Node* DifNode (const Node* node) {
    switch (node->type) {
        case NUM:
            return _NUM (0);
        case VAR:
            return _NUM (1);
        case SUM:
            return _SUM (dL, dR);
        case SUB:
            return _SUB (dL, dR);
        case MUL:
            return _SUM (_MUL (dL, cR), _MUL (cL, dR));
        case DIV:
            return _DIV (_SUB (_MUL (dL, cR), _MUL (cL, dR)), _POW (cR, _NUM (2)));
        case SIN:
            return _MUL (_COS (cR), dR);
        case COS:
            return _MUL (_NUM (-1), _MUL (_SIN (cR), dR));
        case TG:
            return _DIV (dR, _POW (_COS (cR), _NUM (2)));
        case CTG:
            return _DIV (_MUL (dR, _NUM (-1)), _POW (_SIN (cR), _NUM (2)));
        case LN:
            return _DIV (dR, cR);
        case ARCTG:
            return _DIV (dR, _SUM (_NUM(1), _POW (cR, _NUM (2))));
        case POW:
            return _MUL (_MUL (cR, _POW (cL, _SUB (cR, _NUM (1)))), dL);
        case SH:
            return _MUL (_CH (cR), dR);
        case CH:
            return _MUL (_SH (cR), dR);
        case TH:
            return _DIV (dR, _POW (_CH (cR), _NUM (2)));
        case CTH:
            return _DIV (_MUL (dR, _NUM (-1)), _POW (_SH (cR), _NUM (2)));
        default:
            printf ("Undifined type of Node in DifNode()\n");
            break;

    }
    return nullptr;
}

Node* CopyNode (Node* root) {

    if (root) {
        switch (root->type) {
            case NUM:
                return  _NUM (root->num);
            case VAR:
                return  _VAR("x");
            case MUL:
                return  _MUL (CopyNode (_Lf), CopyNode (_R));
            case DIV:
                return _DIV (CopyNode (_Lf), CopyNode (_R));
            case SUM:
                return _SUM (CopyNode (_Lf), CopyNode (_R));
            case SUB:
                return _SUB (CopyNode (_Lf), CopyNode (_R));
            case SIN:
                return _SIN (CopyNode (_R));
            case COS:
                return _COS (CopyNode (_R));
            case TG:
                return _TG (CopyNode (_R));
            case CTG:
                return _CTG (CopyNode (_R));
            case LN:
                return _LN (CopyNode (_R));
            case ARCTG:
                return _ARCTG (CopyNode (_R));
            case POW:
                return _POW (CopyNode (_Lf), CopyNode (_R));
            case SH:
                return _SH (CopyNode (_R));
            case CH:
                return _CH (CopyNode (_R));
            case TH:
                return _TH (CopyNode (_R));
            case CTH:
                return _CTH (CopyNode (_R));
            default:
                return nullptr;
        }
    }
    return nullptr;
}

void DelNode (Node* node) {
    free (node->data);
    free (node->left);
    free (node->right);
}

void DeleteTree (Node* root) {

    if (root) {
        DeleteTree (_Lf);
        DeleteTree (_R);
        DelNode (root);
    }
}

void TreeToLaTex (Node* root, Node* d_root, FILE* f_tex) {
    fprintf (f_tex, "\\documentclass[a4paper,12pt]{article}\n"
                    "\\usepackage[T2A]{fontenc}\n"
                    "\\usepackage[utf8]{inputenc}\n"
                    "\\usepackage[english,russian]{babel}\n"
                    "\n"
                    "\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools} \n"
                    "\n"
                    "\\usepackage{wasysym}\n"
                    "\n"
                    "\\author{Беляев Анастасиус}\n"
                    "\\title{Небольшой пример взятия производной}\n"
                    "\\date{\\today}\n"
                    "\n"
                    "\\begin{document}\n"
                    "\n"
                    "\\maketitle\n"
                    "\\subsection{Решим простой пример}\n"
                    "\n"
                    "{\\Large Найти производную функции \\\\ $f(x)=");
    SaveTree (root, 0, f_tex);
    fprintf (f_tex, "$:\n"
                    "\\begin{center}\n"
                    "\\begin{math}\n"
                    "f^\\prime(x)=");
    SaveTree (d_root, 0, f_tex);
    fprintf (f_tex,"\n"
                   "\\end{math}\n"
                   "\\end{center}\n"
                   "}\n");
    fprintf (f_tex, "{\\Large Разложим по формуле Маклорена:}\n");
    MaklorenSeries (root, 5, f_tex);
    fprintf (f_tex, "\\section {Найдем 5 производную от функции из предыдущего примера.}\n"
                    "{\\Large После небольшого количества несложных преобразований получим:\n"
                    "\\begin{center}\n"
                    "\\begin{math}\n"
                    "f^\\prime(x)=");
    Node* dd_root = NDifNode (root, 5);
    SaveTree (dd_root, 0, f_tex);
    fprintf (f_tex, "\n"
                    "\\end{math}\n"
                    "\\end{center}\n"
                    "}\n"
                    "\\end{document}");

    DeleteTree (dd_root);
    fclose (f_tex);
}

void SaveTree (Node* node, int RootType, FILE* f_sav) {
    if (node) {
        if (((node->type == SUM || node->type == SUB) && (RootType == MUL  || RootType == POW) )
            || RootType > FUNCCOL
            || (RootType == POW && node->type > FUNCCOL)
            || ((node->type == MUL || node->type == DIV) && RootType == POW)
            || (node->type == NUM && node->num < 0)) {
            fprintf (f_sav, "(");
        }

        if (node->type == DIV) {
            fprintf (f_sav, "\\frac {");
        }

        SaveTree (node->left, node->type, f_sav);

        if (node->type == DIV) {
            fprintf (f_sav, "}");
        }


        if (node->type != DIV ) {
            switch (node->type) {
                case NUM:
                    fprintf (f_sav, "%lg", node->num);
                    break;
                case MUL:
                    fprintf(f_sav, "\\cdot ");
                    break;
                default:
                    fprintf(f_sav, "%s", node->data);
            }
        }


        if (node->type == DIV || node->type == POW) {
            fprintf (f_sav, "{");
        }

        SaveTree (node->right, node->type, f_sav);

        if (node->type == DIV || node->type == POW) {
            fprintf (f_sav, "}");
        }

        if (((node->type == SUM || node->type == SUB) && (RootType == MUL  || RootType == POW) )
            || RootType > FUNCCOL
            || (RootType == POW && node->type > FUNCCOL)
            || ((node->type == MUL || node->type == DIV) && RootType == POW)
            || (node->type == NUM && node->num < 0)) {
            fprintf (f_sav, ")");
        }



    }
}

void TreePrint (Node* root, FILE* f_out) {
    assert(root);
    assert(f_out);


    fprintf (f_out, "digraph {\n");

    NodePrint(root, f_out);
    PrintNods (root, f_out);

    fprintf(f_out, "}\n");
    fclose(f_out);
}

void NodePrint (Node* node, FILE* f_out) {
    if (node->data)
        fprintf (f_out, "node%p [label=\"%s\", shape=box];\n", node, node->data);
    else
        fprintf (f_out, "node%p [label=\"%.2lf\", shape=box];\n", node, node->num);

}

void PrintNods (Node* node, FILE* f_out) {
    assert (node);
    assert (f_out);

    if (node->left != nullptr) NodePrint (node->left, f_out);
    if (node->right != nullptr) NodePrint (node->right, f_out);

    if (node->left != nullptr) fprintf (f_out, "node%p -> node%p\n", node, node->left);
    if (node->right != nullptr) fprintf (f_out, "node%p -> node%p\n", node, node->right);

    if (node->right != nullptr) PrintNods (node->right, f_out);
    if (node->left != nullptr) PrintNods (node->left,  f_out);
}
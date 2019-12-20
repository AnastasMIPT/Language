#include <stdio.h>
#include <AnastasLib\Words.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define _KEYWORD(type) CreateNode (type, #type, nullptr, nullptr)
#define _NewEl(type)                                       \
else if ( strcmp (#type, data) == 0)                                      \
    root =  CreateNode (type, #type, nullptr, nullptr);    \

#define _NewTerm(dat, type)   \
else if (strcmp (dat, data) == 0)                   \
    root = CreateNode (type, data, nullptr, nullptr);      \


#define _Lf root->left
#define _R root->right

const int DataSize = 50;


struct Node
{
    char* data;
    double num;
    Node* left;
    Node* right;
    int type;
};


Node* CreateNode (int type, const char* data, Node* left, Node* right);
Node* CreateNode (int type, const char* data, Node* left, Node* right, double num);
Node* CreateNode (double num);
void TreePrint (Node* root, FILE* f_out);
void NodePrint (Node* node, FILE* f_out);
void PrintNods (Node* node, FILE* f_out);
void DelNode (Node* node);
void DeleteTree (Node* root);
Node* GetTreeFromFile (Node* root, FILE* f_in);
int Hash (const char* str);
void POPargs (Node* root, FILE* f_out, int ColTabs);
void TreeToProgram (Node* root, FILE* f_out, int ColTabs);


int main () {
    FILE* f_in  = fopen ("F:\\Programming\\Language\\cmake-build-debug\\tree.txt", "r");
    FILE* f_out = fopen ("F:\\Graphs\\output.dot", "w");

    Node* root;
    root = GetTreeFromFile (root, f_in);


    TreePrint (root, f_out);
    fclose (f_out);

    FILE* f_sav = fopen ("Program.txt", "w");

    TreeToProgram (root, f_sav, 0);
    DeleteTree (root);

    return 0;
}

void Tabs (int Col, FILE* f_out) {
    for (int i = 0; i < Col; i++)
        fprintf (f_out, "\t");
}

void TreeToProgram (Node* root, FILE* f_out, int ColTabs) {
    if (root) {
        int buf = 0;
        switch (root->type) {
            case START:
                fprintf (f_out, "%s\n", Words[START]);
                TreeToProgram (_R, f_out, ColTabs);
                fprintf (f_out, "end");
                break;
            case D:
                TreeToProgram (_R, f_out, ColTabs);
                TreeToProgram (_Lf, f_out, 0);
                break;
            case DEF:
                fprintf (f_out, "%s ", Words[DEF]);
                fprintf (f_out, "%s ", _R->data);
                fprintf (f_out, Words[SKOBKA1]);
                POPargs (_Lf, f_out, 0);
                fprintf (f_out, "%s\n",Words[SKOBKA2]);
                TreeToProgram (_R, f_out, ColTabs);
                break;
            case FUNC:
                TreeToProgram (_R, f_out, ColTabs);
                break;
            case CALL:
                fprintf (f_out, "%s ", _R->data);
                fprintf (f_out, Words[SKOBKA1]);
                POPargs (_Lf, f_out, 0);
                fprintf (f_out, "%s",Words[SKOBKA2]);
                TreeToProgram (_R, f_out, ColTabs);
                break;
            case COMMA:
                TreeToProgram (_R, f_out, ColTabs);
                TreeToProgram (_Lf, f_out, ColTabs);
                break;
            case B:
                Tabs (ColTabs, f_out);
                fprintf (f_out, "%s\n", Words[BLOCK_ST]);
                TreeToProgram (_R, f_out, ColTabs + 1);
                Tabs (ColTabs, f_out);
                fprintf (f_out, "%s\n", Words[BLOCK_END]);
                break;
            case OP:
                Tabs (ColTabs, f_out);
                TreeToProgram (_R, f_out, ColTabs);
                TreeToProgram (_Lf, f_out, ColTabs);
                break;
            case ASSIGN:
                TreeToProgram (_Lf, f_out, ColTabs);
                fprintf (f_out, " %s ", Words[ASSIGN]);
                TreeToProgram (_R, f_out, ColTabs);
                fprintf (f_out, "%s\n", Words[COMMA_POINT]);
                break;
            case IF:

                fprintf (f_out, "%s ", Words[IF]);

                TreeToProgram(_Lf, f_out, ColTabs);
                TreeToProgram(_R, f_out, ColTabs);
                break;
            case EQUAL:
                fprintf (f_out, "%s",Words[SKOBKA1]);
                TreeToProgram(_Lf, f_out, ColTabs);
                fprintf (f_out, " %s ", Words[EQUAL]);
                TreeToProgram(_R, f_out, ColTabs);
                fprintf (f_out, "%s\n", Words[SKOBKA2]);
                break;
            case UNEQUAL:
                fprintf (f_out, "%s",Words[SKOBKA1]);
                TreeToProgram(_Lf, f_out, ColTabs);
                fprintf (f_out, " %s ", Words[UNEQUAL]);
                TreeToProgram(_R, f_out, ColTabs);
                fprintf (f_out, "%s\n",Words[SKOBKA2]);
                break;
            case MORE:
                fprintf (f_out, "%s",Words[SKOBKA1]);
                TreeToProgram(_Lf, f_out, ColTabs);
                fprintf (f_out, " %s ", Words[MORE]);
                TreeToProgram(_R, f_out, ColTabs);
                fprintf (f_out, "%s\n",Words[SKOBKA2]);
                break;
            case SUM:
                TreeToProgram(_R, f_out, ColTabs);
                fprintf (f_out, " %s ", Words[SUM]);
                TreeToProgram(_Lf, f_out, ColTabs);
                break;
            case SUB:
                TreeToProgram(_Lf, f_out, ColTabs);
                fprintf (f_out, " %s ", Words[SUB]);
                TreeToProgram(_R, f_out, ColTabs);
                break;
            case MUL:
                TreeToProgram(_Lf, f_out, ColTabs);
                fprintf (f_out, " %s ", Words[MUL]);
                TreeToProgram(_R, f_out, ColTabs);
                break;
            case DIV:
                TreeToProgram(_Lf, f_out, ColTabs);
                fprintf (f_out, " %s ", Words[DIV]);
                TreeToProgram(_R, f_out, ColTabs);
                break;
            case RETURN:
                fprintf (f_out, "%s", Words[RETURN]);
                if (_R) fprintf (f_out, " ");
                TreeToProgram(_R, f_out, ColTabs);
                fprintf (f_out, "%s\n", Words[COMMA_POINT]);
                break;
            case OUTPUT:
                fprintf (f_out, "%s ", Words[OUTPUT]);
                fprintf (f_out, "%s",Words[SKOBKA1]);
                TreeToProgram(_R, f_out, ColTabs);
                fprintf (f_out, "%s\n",Words[SKOBKA2]);
                break;
            case INPUT:
                fprintf (f_out, "%s ", Words[INPUT]);
                fprintf (f_out, "%s",Words[SKOBKA1]);
                TreeToProgram(_R, f_out, ColTabs);
                fprintf (f_out, "%s\n",Words[SKOBKA2]);
                break;
            case SQRT:
                fprintf (f_out, "%s ", Words[SQRT]);
                fprintf (f_out, "%s",Words[SKOBKA1]);
                TreeToProgram(_R, f_out, ColTabs);
                fprintf (f_out, "%s",Words[SKOBKA2]);
                break;
            case VAR:
                fprintf (f_out, "%s", root->data);
                break;
            case NUM:
                fprintf (f_out, "%lg", root->num);
                break;
            default:
                printf ("\n! ERROR ! Неизвестный узел %s, тип: %d", root->data, root->type);
                break;
        }
    }
}

void POPargs (Node* root, FILE* f_out, int ColTabs) {

    if (root) {
        assert (root->type = COMMA);
        TreeToProgram(root->right, f_out, ColTabs);
        if (_Lf) fprintf (f_out, ", ");
        POPargs(_Lf, f_out, ColTabs);
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
    _NewEl(OP)
    _NewEl(D)
    _NewEl(B)
    _NewEl(END)
    _NewEl(IF)
    _NewEl(WHILE)
    _NewEl(BLOCK_ST)
    _NewEl(BLOCK_END)
    _NewEl(SKOBKA1)
    _NewEl(SKOBKA2)
    _NewEl(ASSIGN)
    _NewEl(DEF)
    _NewEl(EQUAL)
    _NewEl(UNEQUAL)
    _NewEl(MORE)
    _NewEl(COMMA_POINT)
    _NewEl(RETURN)
    _NewEl(INPUT)
    _NewEl(OUTPUT)
    _NewEl(CALL)
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

    root->left  = GetTreeFromFile (root->left,  f_in);
    root->right = GetTreeFromFile (root->right, f_in);
    fscanf (f_in,")");
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

void DeleteTree (Node* root) {

    if (root) {
        DeleteTree (_Lf);
        DeleteTree (_R);
        DelNode (root);
    }
}

void DelNode (Node* node) {
    free (node->data);
    free (node->left);
    free (node->right);
}

void TreePrint (Node* root, FILE* f_out) {
    assert(root);
    assert(f_out);


    fprintf (f_out, "digraph {\n");

    NodePrint (root, f_out);
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
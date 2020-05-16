//
// Created by Admin on 11.12.2019.
//

#ifndef LANGUAGE_WORDS_H
#define LANGUAGE_WORDS_H

#endif //LANGUAGE_WORDS_H

enum {
    START,
    END,
    IF,
    WHILE,
    BLOCK_ST,
    BLOCK_END,
    COMMA_POINT,
    COMMA,
    SKOBKA1,
    SKOBKA2,
    ASSIGN,
    RETURN,
    INPUT,
    OUTPUT,
    BREAK,
    DEF,
    EQUAL,
    UNEQUAL,
    MORE,
    COL_WORDS,
    SIN,
    COS,
    TG,
    CTG,
    ARCTG,
    LN,
    SH,
    CH,
    TH,
    CTH,
    SQRT,
    DIFF,
    FUNCCOL,

    NUM,
    SUM,
    SUB,
    MUL,
    POW,
    DIV,
    VAR,
    FUNC,
    CALL,
    OP,
    NEW_LINE,
    B,
    D


};

const char* Words[]  = {
        "start",
        "end",
        "if",
        "while",
        "{",
        "}",
        ";",
        ",",
        "(",
        ")",
        "=",
        "return",
        "input",
        "output",
        "break",
        "def",
        "equal",
        "unequal",
        "more",
        "",
        "sin",
        "cos",
        "tg",
        "ctg",
        "arctg",
        "ln",
        "sh",
        "ch",
        "th",
        "cth",
        "sqrt",
        "diff",
        "",
        "",
        "+",
        "-",
        "*",
        "^",
        "/",
};

const int HashTreeWords[] = {
        160291,                       //START
        -1,              //END
        5253,               //IF
        -1,             //WHILE
        -1,                 //BLOCK_START
        -1,                 //BLOCK_END
        -1,                  //COMMA_POINT
        1281,               //ASSIGN
        -1,                //SKOBKA1
        -1,                //SKOBKA2
        16660,                  //ASSIGN
        481160,             //RETURN
        159265,            //INPUT
        481375,            //OUTPUT
        17022,             //DEF
        159045,            //EQUAL
        1447674,           //UNEQUAL
        52751,            //MORE
        -1,                //COL_WORDS
        -1,             //SIN
        -1,             //COS
        -1,               //TG
        -1,             //CTG
        -1,           //ARCTG
        -1,              //LN
        -1,              //SH
        -1,              //CH
        -1,              //TH
        -1,             //CTH
        54460,            //SQRT
        -1,                 //FUNCCOL
        -1,             //NUM
        1280,          //SUM
        1282,          //SUB
        1279,          //MUL
        -1,             //POW
        1284,               //DIV
        -1,             //VAR
        -1,          //FUNC
        52338,               //CALL
        5283,               //OP
        -1,               //NEW_LINE
        1307,               //BLOCK
        1309               //DECLARE
};
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
    SKOBKA1,
    SKOBKA2,
    ASSIGN,
    DEF,
    EQUAL,
    ABOVE,

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
    FUNCCOL,

    NUM,
    SUM,
    SUB,
    MUL,
    POW,
    DIV,
    VAR,
    OP,
    NEW_LINE,
    BLOCK


};

const char* Words[]  = {
        "start",
        "end",
        "if",
        "while",
        "{",
        "}",
        "\n",
        "(",
        ")",
        "=",
        "def",
        "equal",
        ">",
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
        "cth"

};

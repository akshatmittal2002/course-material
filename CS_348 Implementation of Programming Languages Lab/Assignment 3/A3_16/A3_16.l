%{

    // ---------------------------------------- //
    //          CS348 Assignment 3              //
    //  By Group 16: Ujwal Kumar    200101100   //
    //               Akshat Mittal  200101011   //
    // ---------------------------------------- //
    #include "stdio.h"
    #define KEYWORD                 258
    #define IDENTIFIER              259
    #define INT_CONST               260
    #define CHAR_CONST              261
    #define STRING_LIT              262
    #define PUNCTUATOR              263
    #define MULTI_COMMENT_BEGIN     264
    #define MULTI_COMMENT_END       265
    #define MULTI_COMMENT           266
    #define SINGLE_COMMENT_BEGIN    267
    #define SINGLE_COMMENT_END      268
    #define SINGLE_COMMENT          269
    #define WHITESPACE              270

%}

KEYWORD             "char"|"else"|"for"|"if"|"int"|"return"|"void"

ID                  [_a-zA-Z][_a-zA-Z0-9]*

SIGN_OPT            [-+]?
INT_CONST           {SIGN_OPT}[1-9][0-9]*|[0]

ESC_SEQ             "\\\'"|"\\\""|"\?"|"\\"|"\a"|"\b"|"\f"|"\n"|"\r"|"\t"|"\v"
C_CHAR          	[^\'\n\\]|{ESC_SEQ}
C_CHAR_SEQ      	{C_CHAR}+
CHAR_CONST      	\'{C_CHAR_SEQ}\'

S_CHAR          	[^\"\n\\]|{ESC_SEQ}

PUNC_1              "["|"]"|"("|")"|"{"|"}"|"->"|"&"|"*"|"+"|"-"|"/"|"%"|"!"|"?"
PUNC_2              "<"|">"|"<="|">="|"=="|"!="|"&&"|"||"|"="|":"|";"|","
PUNC                {PUNC_1}|{PUNC_2}

WS              	[ \t\n]

%x MULTI_CMT
%x SINGLE_CMT
%x STR

%%

{KEYWORD}           { return KEYWORD; }
{ID}                { return IDENTIFIER; }
{INT_CONST}         { return INT_CONST; }
{CHAR_CONST}        { return CHAR_CONST; }
{PUNC}              { return PUNCTUATOR; }

{WS}            	{ return WHITESPACE; }

<INITIAL>"\""       { BEGIN(STR); }
<STR>{S_CHAR}*      { return STRING_LIT; }
<STR>"\""           { BEGIN(INITIAL); }

<INITIAL>"/*"       { BEGIN(MULTI_CMT); return MULTI_COMMENT_BEGIN; }
<MULTI_CMT>"*/"     { BEGIN(INITIAL); return MULTI_COMMENT_END; }
<MULTI_CMT>.        { return MULTI_COMMENT; }
<MULTI_CMT>"\n"     { return MULTI_COMMENT; }

<INITIAL>"//"       { BEGIN(SINGLE_CMT); return SINGLE_COMMENT_BEGIN; }
<SINGLE_CMT>"\n"    { BEGIN(INITIAL); return SINGLE_COMMENT_END; }
<SINGLE_CMT>.       { return SINGLE_COMMENT; }

%%
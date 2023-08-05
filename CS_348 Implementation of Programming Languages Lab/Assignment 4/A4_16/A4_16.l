%{

    // ---------------------------------------- //
    //          CS348 Assignment 4              //
    //  By Group 16: Ujwal Kumar    200101100   //
    //               Akshat Mittal  200101011   //
    // ---------------------------------------- //
    #include "stdio.h"
    #include "y.tab.h"

    int line_num = 1;

%}

ID                  [_a-zA-Z][_a-zA-Z0-9]*

INT_CONST           [1-9][0-9]*|[0]+

ESC_SEQ             "\\\'"|"\\\""|"\?"|"\\"|"\a"|"\b"|"\f"|"\n"|"\r"|"\t"|"\v"
C_CHAR          	[^\'\n\\]|{ESC_SEQ}
C_CHAR_SEQ      	{C_CHAR}+
CHAR_CONST      	\'{C_CHAR_SEQ}\'
S_CHAR          	[^\"\n\\]|{ESC_SEQ}
WS              	[ \t\n]

%x MULTI_CMT
%x SINGLE_CMT
%x STR
%option yylineno

%%

"char"              {return CHAR; }
"else"              {return ELSE; }
"for"               {return FOR; }
"if"                {return IF; }
"int"               {return INT; }
"return"            {return RETURN; }
"void"              {return VOID; }

{ID}                { yylval.IDvalue = yytext; return IDENTIFIER; }
{INT_CONST}         { yylval.intValue = atoi(yytext); return INT_CONST; }
{CHAR_CONST}        { yylval.stringValue = yytext; return CHAR_CONST; }
"\n"                { line_num++; printf("==================== Line No = %d ====================\n", line_num); }

{WS}            	{ }

<INITIAL>"\""       { BEGIN(STR); }
<STR>{S_CHAR}*      { yylval.stringValue = yytext; return STRING_LIT; }
<STR>"\""           { BEGIN(INITIAL); }

<INITIAL>"/*"       { BEGIN(MULTI_CMT);}
<MULTI_CMT>"*/"     { BEGIN(INITIAL);}
<MULTI_CMT>.        { }
<MULTI_CMT>"\n"     { line_num++; printf("==================== Line No = %d ====================\n", line_num); }

<INITIAL>"//"       { BEGIN(SINGLE_CMT); }
<SINGLE_CMT>"\n"    { line_num++; printf("==================== Line No = %d ====================\n", line_num); BEGIN(INITIAL); }
<SINGLE_CMT>.       { }


"["                 {return '['; }
"]"                 {return ']'; }
"("                 {return '('; }
")"                 {return ')'; }
"{"                 {return '{'; }
"}"                 {return '}'; }
"->"                {return ARROW; }
"&"                 {return '&'; }
"*"                 {return MULT; }
"+"                 {return '+'; }
"-"                 {return MINUS; }
"/"                 {return '/'; }
"%"                 {return '%'; }
"?"                 {return '?'; }
">"                 {return '>'; }
"<"                 {return '<'; }
"<="                {return LEQ; }
">="                {return GEQ; }
"=="                {return EQ; }
"!="                {return NEQ; }
"&&"                {return AND; }
"||"                {return OR; }
"="                 {return '='; }
":"                 {return ':'; }
";"                 {return ';'; }
","                 {return ','; }


%%
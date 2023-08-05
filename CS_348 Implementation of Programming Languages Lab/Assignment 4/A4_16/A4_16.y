%{
    #include "stdio.h"
    #include <string.h>


    extern int yylex();
    extern int yylineno;
    extern char* yytext;
    void yyerror(char* s);

    char type[10];
    char name[40];
    char value[100];
    char pointer = ' ';
    int dimension;
    int length;
    char func = ' ';
    char funcname[40];

    #define STsize 1000
    int STindex = 0;

    struct STentry {
        char type[40];
        char name[40];
        char value[100];
        char pointer;
        char func;
        int lineno;
        int dimension;
        int length;
    };

    struct STentry ST[STsize];

    void addST();
    void printST();
%}

%union {
    int intValue;
    char* IDvalue;
    char* stringValue;
}

%token CHAR ELSE FOR IF INT RETURN VOID

%type <IDvalue> function_definition declarator direct_declarator identifier

%token <IDvalue> IDENTIFIER 
%token <stringValue> STRING_LIT
%token <intValue> INT_CONST
%token <stringValue> CHAR_CONST

%token ARROW MULT MINUS LEQ GEQ EQ NEQ AND OR 

%nonassoc ')'
%nonassoc ELSE
%start start_symbol

%%

identifier: IDENTIFIER
            {
                printf("identifier <%s> \n", $1);
                strcpy(name, $1);
                $$ = strdup($1);
            }
            ;

constant:   
            INT_CONST
            {   
                printf("constant -> int-const <%d>\n", $1);
                sprintf(value, "%d", $1);
            }
            | CHAR_CONST
            {
                printf("constant -> char-const <%s>\n", $1);
                sprintf(value, "%s", $1);
            }
            ;

primary_expression:
                    identifier
                    { printf("primary_expression -> identifier\n");}
                    | constant
                    { printf("primary_expression -> constant\n"); }
                    | STRING_LIT
                    { 
                        printf("primary_expression -> string-literal <%s>\n", $1); 
                        sprintf(value, "%s", $1);
                    }
                    | '(' expression ')'
                    { printf("primary_expression -> ( expression )\n"); }
                    ;

postfix_expression:
                    primary_expression
                    { printf("postfix_expression -> primary_expression\n"); }
                    | postfix_expression '[' expression ']'
                    { printf("postfix_expression -> postfix_expression [ expression ]\n"); }
                    | postfix_expression '(' argument_expression_list_opt ')'
                    { printf("postfix_expression -> postfix_expression ( argument_expression_list_opt )\n"); }
                    | postfix_expression ARROW identifier
                    { printf("postfix_expression -> postfix_expression -> identifier\n"); }


argument_expression_list:
                            assignment_expression
                            { printf("argument_expression_list -> assignment_expression\n"); }
                            | argument_expression_list ',' assignment_expression   
                            { printf("argument_expression_list -> argument_expression_list , assignment_expression\n"); }

argument_expression_list_opt:
                                argument_expression_list
                                {printf("argument_expression_list_opt -> argument_expression_list\n"); }
                                |
                                {printf("argument_expression_list_opt -> EPSILON\n"); }
                                ;

unary_expression:
                    postfix_expression
                    { printf("unary_expression -> postfix_expression\n"); }
                    | unary_operator unary_expression
                    { printf("unary_expression -> unary_operator unary_expression\n"); }
                    ; 

unary_operator: 
                '&' 
                { printf("unary_operator -> &\n"); }
                | MULT
                { printf("unary_operator -> *\n"); }
                | '+' 
                { printf("unary_operator -> +\n"); }
                | MINUS
                { printf("unary_operator -> -\n"); }
                | '!'
                { printf("unary_operator -> !\n"); }
                ;

multiplicative_expression:
                            unary_expression
                            { printf("multiplicative_expression -> unary_expression\n"); }
                            | multiplicative_expression MULT unary_expression
                            { printf("multiplicative_expression -> multiplicative_expression * unary_expression\n"); }
                            | multiplicative_expression '/' unary_expression
                            { printf("multiplicative_expression -> multiplicative_expression / unary_expression\n"); }
                            | multiplicative_expression '%' unary_expression     
                            { printf("multiplicative_expression -> multiplicative_expression modulo unary_expression\n"); }
                            ;

additive_expression:        
                        multiplicative_expression
                        { printf("additive_expression -> multiplicative_expression\n"); }
                        | additive_expression '+' multiplicative_expression
                        { printf("additive_expression -> additive_expression + multiplicative_expression\n"); }
                        | additive_expression MINUS multiplicative_expression
                        { printf("additive_expression -> additive_expression - multiplicative_expression\n"); }
                        ;

relational_expression:
                        additive_expression
                        { printf("relational_expression -> aditive_expression\n"); }
                        | relational_expression '<' additive_expression
                        { printf("relational_expression -> relational_expression < additive_expression\n"); }
                        | relational_expression '>' additive_expression
                        { printf("relational_expression -> relational_expression > additive_expression\n"); }
                        | relational_expression LEQ additive_expression
                        { printf("relational_expression -> relational_expression <= additive_expression\n"); }
                        | relational_expression GEQ additive_expression
                        { printf("relational_expression -> relational_expression >= additive_expression\n"); }
                        ;


equality_expression:
                        relational_expression
                        { printf("equality_expression -> relational_expression\n"); }
                        | equality_expression EQ relational_expression
                        { printf("equality_expression -> equality_expression == relational_expression\n"); }
                        | equality_expression NEQ relational_expression
                        { printf("equality_expression -> equality_expression != relational_expression\n"); }
                        ;

logical_AND_expression:
                        equality_expression
                        { printf("logical_AND_expression -> equality_expression\n"); }
                        | logical_AND_expression AND equality_expression
                        { printf("logical_AND_expression -> AND_expression && equality_expression\n");}
                        ;

logical_OR_expression:
                        logical_AND_expression
                        { printf("logical_OR_expression -> logical_AND_expression\n"); }
                        | logical_OR_expression OR logical_AND_expression
                        { printf("logical_OR_expression -> logical_OR_expression || logical_AND_expression\n"); }
                        ;

conditional_expression:
                        logical_OR_expression
                        { printf("conditional_expression -> logical_OR_expression\n"); }
                        | logical_OR_expression '?' expression ':' conditional_expression
                        { printf("conditional_expression -> logical_OR_expression ? expression : conditional_expression\n"); }
                        ;

assignment_expression:
                        conditional_expression
                        { printf("assignment_expression -> conditional_expression\n"); }
                        | unary_expression '=' assignment_expression
                        { printf("assignment_expression -> unary_expression assignment_operator assignment_expression\n"); }
                        ;

expression:
            assignment_expression
            {printf("expression -> assignment_expression\n"); }
            ;

declaration:
                type_specifier init_declarator ';'
                { printf("declaration -> type_specifier init_declarator ;\n"); addST();}
                ;

init_declarator:
                    declarator
                    { printf("init_declarator -> declarator\n"); }
                    | declarator '=' initializer
                    { printf("init_declarator -> declarator = initializer\n"); }
                    ;

type_specifier:
                VOID
                { printf("type_specifier -> void\n"); strcpy(type, yytext); }
                | CHAR
                { printf("type_specifier -> char\n"); strcpy(type, yytext); }
                | INT
                { printf("type_specifier -> int\n"); strcpy(type, yytext); }
                ;

declarator:
                pointer_opt direct_declarator
                { printf("declarator -> pointer_opt direct_declarator\n"); $$ = strdup($2); }
                ;

direct_declarator:
                    identifier
                    {printf("direct_declarator -> identifier\n"); }
                    |
                    identifier '[' INT_CONST ']'
                    {
                        printf("direct_declarator -> identifier [ int-const ]\n"); 
                        dimension = 1;
                        length = $3;
                    }
                    |
                    identifier '(' parameter_list_opt ')'
                    { printf("direct_declarator -> identifier ( parameter_list_opt )\n"); $$ = strdup($1);}


pointer_opt:
                pointer
                { printf("pointer_opt -> pointer\n"); pointer='*'; }
                | 
                { printf("pointer_opt -> EPSILON\n");}
                ;

pointer:        MULT
                { printf("pointer -> MULT\n");}
                ;



parameter_list_opt:
                parameter_list
                {printf("parameter_list_opt -> parameter_list\n"); }
                |
                {printf("parameter_list_opt -> EPSILON\n"); }
                ;

parameter_list:
                parameter_declaration
                {printf("parameter_list -> parameter_declaration\n"); }
                |
                parameter_list ',' parameter_declaration
                {printf("parameter_list -> parameter_list , parameter_declaration\n"); }
                ;


parameter_declaration: 
                type_specifier pointer_opt identifier_opt
                {printf("parameter_declaration -> type_specifier pointer_opt identifier_opt\n"); }

identifier_opt:
                identifier
                {printf("identifier_opt -> identifier\n"); }
                |
                {printf("identifier_opt -> EPSILON\n"); }
                ;

initializer:
                assignment_expression
                {printf("initializer -> assignment_expression\n"); }

statement:
            | compound_statement
            { printf("statement -> compound_statement\n"); }
            | expression_statement
            { printf("statement -> expression_statement\n"); }
            | selection_statement
            { printf("statement -> selection_statement\n"); }
            | iteration_statement
            { printf("statement -> iteration_statement\n"); }
            | jump_statement
            { printf("statement -> jump_statement\n"); }
            ;
            

compound_statement:     
                        '{' block_item_list_opt '}'
                        { printf("compound_statement -> { block_item_list_opt }\n"); }
                        ;

block_item_list_opt:
                    block_item_list_opt block_item
                    { printf("block_item_list_opt -> block_item_list_opt block_item\n"); }
                    |
                    { printf("block_item_list_opt -> EPSILON\n"); }
                    ;

block_item:
            declaration
            { printf("block_item -> declaration\n"); }
            | statement
            { printf("block_item -> statement\n"); }
            ;

expression_statement:
                        expression_opt ';'
                        { printf("expression_statement-> expression_opt ;\n"); }
                        ;

selection_statement:
                    IF '(' expression ')' statement
                    { printf("selection_statement -> if ( expression ) statement\n"); }
                    | IF '(' expression ')' statement ELSE statement
                    { printf("selection_statement -> if ( expression ) statement else statement\n"); }

iteration_statement:
                    FOR '(' expression_opt ';' expression_opt ';' expression_opt ')' statement
                    { printf("iteration_statement -> for ( expression_opt ; expression_opt ; expression_opt ) statement\n"); }

expression_opt:
                expression
                {printf("expression_opt -> expression\n"); }
                |
                {printf("expression_opt -> EPSILON\n"); }
                ;

jump_statement: 
                RETURN expression_opt ';'
                { printf("jump_statement -> return expression_opt ;\n"); }
                ;

start_symbol:
                translation_unit
                { printST(); }
                ;

translation_unit:
                external_declaration
                { printf("translation_unit -> external_declaration\n"); }
                |
                translation_unit external_declaration
                { printf("translation_unit -> translation_unit external_declaration\n"); }
                ;


external_declaration:
                function_definition
                { printf("external_declaration -> function_definition\n"); }
                |
                declaration
                { printf("external_declaration -> declaration\n"); }
                ;

function_definition:
                type_specifier declarator declaration_list_opt  compound_statement
                { 
                    printf("function_definition -> type_specifier declarator declaration_list_opt  compound_statement\n"); 
                    strcpy(type, "func");
                    strcpy(name, $2);
                    func = '*';
                    addST();
                }
                ;


declaration_list_opt:
                declaration_list
                { printf("declaration_list_opt -> declaration_list\n"); }
                |
                { printf("declaration_list_opt -> EPSILON\n"); }
                ;


declaration_list:
                declaration
                { printf("declaration_list -> declaration\n"); }
                |
                declaration_list declaration
                { printf("declaration_list -> declaration_list declaration\n"); }
                ;

%%

void yyerror(char* msg)
{
    printf("Error | %d: %s at '%s'\n", yylineno, msg, yytext);
}

void addST(){

    strcpy(ST[STindex].type, type);
    strcpy(ST[STindex].name, name);

    if(func != '*')
        strcpy(ST[STindex].value, value);
    else
        strcpy(ST[STindex].value, "");
    
    ST[STindex].lineno = yylineno;
    ST[STindex].pointer = pointer;
    ST[STindex].func = func;
    ST[STindex].dimension = dimension;
    ST[STindex].length = length;
    
    dimension = 0;
    length = 0;
    strcpy(value, "");
    strcpy(name, "");
    strcpy(type, "");
    pointer = ' ';
    func = ' ';

    STindex++;
}

void printST(){
    
    printf("\n\n--------------------------SYMBOL TABLE--------------------------\n");
    printf("===============================================================================================\n");
    printf("| type  | ptr | func |      name       | dimension | length |           value           | lno |\n");
    printf("===============================================================================================\n");
    
    for(int i=0; i<STindex; i++){
        
        printf(
                "| %5s | %3c | %4c | %15s | %9d | %6d | %25s | %3d |\n", 
                ST[i].type, 
                ST[i].pointer, 
                ST[i].func,
                ST[i].name, 
                ST[i].dimension,
                ST[i].length,
                ST[i].value, 
                ST[i].lineno
            );
    }
    printf("===============================================================================================\n");
}

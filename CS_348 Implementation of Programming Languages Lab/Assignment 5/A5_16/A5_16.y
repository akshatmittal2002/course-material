%{
    #include <bits/stdc++.h>
    #include "A5_16_translator.h"
    using namespace std;

    // Lex external definitions
    extern int yylex();
    extern char* yytext;                   
    extern int yylineno;                      
    void yyerror(string s);                
                     
    // Custom external definitions
    extern int nextinstr;                  
    extern QuadArr quadList;             
    extern SymTab globalST;           
    extern SymTab* ST;                 

    int strCount = 0;                      
%}

%union {
    // To store basic types
    int intValue;                    
    char charValue;                  
    void* ptr;                     
    string* str;

    // To store types declared in .h file
    SymType* symType;           
    Sym* symp;                  
    DataType types;                
    opcode opc;                    
    Expression* expr;              
    Declaration* dec;              
    vector<Declaration*> *decList; 
    param* prm;                    
    vector<param*> *prmList;       
}

/* Main keywords */
%token CHAR_ FOR IF INT_ RETURN_ VOID_ 

/* Supporting terminals */
%token ARROW LESS_THAN_EQUAL GREATER_THAN_EQUAL EQUAL NOT_EQUAL LOGICAL_AND LOGICAL_OR 

/* TYPES FOR TERMINALS */
%token <str> IDENTIFIER
%token <intValue> INTEGER_CONSTANT
%token <charValue> CHAR_CONSTANT
%token <str> STRING_LITERAL

/* TYPES FOR NON TERMINALS */
// All these are of type Expression
%type <expr> 
        Expression
        primary_expression 
        multiplicative_expression
        additive_expression
        relational_expression
        equality_expression
        logical_and_expression
        logical_or_expression
        conditional_expression
        assignment_expression
        postfix_expression
        unary_expression
        expression_statement
        statement
        compound_statement
        selection_statement
        iteration_statement 
        jump_statement
        block_item
        block_item_list
        initializer
        M
        N


%type <charValue> unary_operator
%type <intValue> pointer
%type <types> type_specifier
%type <dec> direct_declarator init_declarator declarator function_prototype
%type <decList> init_declarator_list
%type <prm> parameter_declaration
%type <prmList> parameter_list parameter_type_list_opt argument_expression_list

%expect 1
%nonassoc ELSE

%start translation_unit

%%

/* Rules to augement grammar */
/* Mainly used for backpatching */
/* Creates a new Expression and stores value of nextinstr in it  */
M: %empty
        {   
        
            $$ = new Expression();
            $$->instr = nextinstr;
        }
        ;

/*  Emit empty goto statement*/
N: %empty
        {
        
            $$ = new Expression();
            $$->nextlist = makelist(nextinstr);
            emit("", "", "", GOTO);
        }
        ;

/* 
    In all these cases, generate a primary Expression to use for
    later.
 */
primary_expression: 
                IDENTIFIER
                {   
                    $$ = new Expression(); 
                    // Get name of identifier
                    string str = *($1);

                    // Create new entry if doesn't exist
                    ST->Lookup(str);         
                    $$->loc = str;           
                }
                | INTEGER_CONSTANT
                {   
                    // Create new temporary for int
                    $$ = new Expression();                 
                    $$->loc = ST->GenerateTemp(INT);

                    // Assign value to temp
                    emit($$->loc, $1, ASSIGN);

                    // Set initial value of Sym in table
                    SymVal* val = new SymVal();
                    val->SetInit($1);                   
                    ST->Lookup($$->loc)->initVal = val;    
                }
                | CHAR_CONSTANT
                {   
                     // Create new temporary for int
                    $$ = new Expression();                 
                    $$->loc = ST->GenerateTemp(CHAR);

                    // Assign value to temp
                    emit($$->loc, $1, ASSIGN);

                    // Set initial value of Sym in table
                    SymVal* val = new SymVal();
                    val->SetInit($1);                   
                    ST->Lookup($$->loc)->initVal = val;    
                }
                | STRING_LITERAL
                {   
                    $$ = new Expression();      
                    // Name of string           
                    $$->loc = ".LC" + to_string(strCount++);

                }
                | '(' Expression ')'
                {
                    $$ = $2;                               
                }
                ;

/* Also of type Expression,
    Used for array access and function calls
 */
postfix_expression:
                primary_expression {}
                | postfix_expression '[' Expression ']'
                {   
                    // New temp
                    SymType to = ST->Lookup($1->loc)->type;     
                    string f = "";
                    if(!($1->fold)) {
                        f = ST->GenerateTemp(INT);                      
                        emit(f, 0, ASSIGN);
                        $1->folder = new string(f);
                    }
                    string temp = ST->GenerateTemp(INT);

                    // Compute address of location
                    emit(temp, $3->loc, "", ASSIGN);
                    emit(temp, temp, "4", MULT);
                    emit(f, temp, "", ASSIGN);
                    $$ = $1;
                }
                | postfix_expression '(' ')'
                {   
                    // Get nested table of function
                    SymTab* funcTable = globalST.Lookup($1->loc)->nestedTable;

                    // Call a function with no parameters
                    emit($1->loc, "0", "", CALL);
                }
                | postfix_expression '(' argument_expression_list ')'
                {   
                    // Get nested table of function
                    SymTab* funcTable = globalST.Lookup($1->loc)->nestedTable;
                    vector<param*> parameters = *($3);                         
                    vector<Sym*> paramsList = funcTable->symbols;

                    // Quad code to push params onto stack
                    for(int i = 0; i < (int)parameters.size(); i++) {
                        emit(parameters[i]->name, "", "", PARAM);              
                    }

                    // Set up return values
                    DataType retType = funcTable->Lookup("RETVAL")->type.type; 
                    if(retType == VOID)                                        
                        emit($1->loc, (int)parameters.size(), CALL);
                    else {                                                     
                        string retVal = ST->GenerateTemp(retType);
                        emit($1->loc, to_string(parameters.size()), retVal, CALL);
                        $$ = new Expression();
                        $$->loc = retVal;
                    }
                }
                | postfix_expression ARROW IDENTIFIER
                {}
                ;

/* 

 */
argument_expression_list: 
                assignment_expression
                {   
                    // We found the first parameter
                    // Create a new vector of parameters
                    param* first = new param();                
                    first->name = $1->loc;
                    first->type = ST->Lookup($1->loc)->type;
                    $$ = new vector<param*>;

                    // Push back the first parameter
                    $$->push_back(first);                      
                }
                | argument_expression_list ',' assignment_expression
                {   
                    // Found next parameter
                    param* next = new param();                 
                    next->name = $3->loc;
                    next->type = ST->Lookup(next->name)->type;
                    $$ = $1;

                    // Pushback the next parameter
                    $$->push_back(next);                       
                }
        ;

/* 
    Unary Expression is has either one of the following operands
    1. & - Address
    2. * - Dereferencing
    3. - - Sign inversion
    4. ! - Logical inversion
 */
unary_expression: 
                postfix_expression  {}
                | unary_operator unary_expression
                {
                    // Do nothign for $1 = +
                    if($1 == '&')
                    {
                        $$ = new Expression();
                        // Generate temp of type pointer
                        $$->loc = ST->GenerateTemp(POINTER);

                        // Emit Quad of reference
                        emit($$->loc, $2->loc, "", REFERENCE);         
                        break;
                    }
                    else if($1 == '*')
                    {
                        $$ = new Expression();
                        // Generate temp of type int
                        $$->loc = ST->GenerateTemp(INT);                    
                        $$->fold = 1;
                        $$->folder = new string($2->loc);

                        // Emit Quad of dereference
                        emit($$->loc, $2->loc, "", DEREFERENCE);       
                        break;
                    }
                    else if($1 == '-')
                    {   
                        $$ = new Expression();
                        // Generate an empty temp
                        $$->loc = ST->GenerateTemp();

                        // Invert the sign using                   
                        emit($$->loc, $2->loc, "", U_MINUS);           
                        break;
                    }
                    else if($1 == '!')
                    {   
                        $$ = new Expression();
                        $$->loc = ST->GenerateTemp(INT);
                                            
                        int temp = nextinstr + 2;
                        emit(to_string(temp), $2->loc, "0", GOTO_EQ); 

                        temp = nextinstr + 3;
                        emit(to_string(temp), "", "", GOTO);
                        emit($$->loc, "1", "", ASSIGN);

                        temp = nextinstr + 2;
                        emit(to_string(temp), "", "", GOTO);
                        emit($$->loc, "0", "", ASSIGN);

                        break;
                    }
                }
                ;

/* 
    Rule to detect unary operators
 */
unary_operator:
            '&'
            {   
                // addr
                $$ = '&';
            }
            | '*'
            {   
                // dereference
                $$ = '*';
            }
            | '+'
            {   
                // unary add
                $$ = '+';
            }
            | '-'
            {   
                // unary sub
                $$ = '-';
            }
            | '!'
            {   
                // not
                $$ = '!';
            }
            ;

/* 
    Multiplicative expressions build upon unary expressions
 */
multiplicative_expression: 
                    unary_expression
                    {
                        $$ = new Expression();

                        // Get type of Sym table entry
                        SymType tp = ST->Lookup($1->loc)->type;
                        
                        // Handle array case
                        if(tp.type == ARRAY) {
                            // Get a temp to store indexed element
                            string t = ST->GenerateTemp(tp.nextType);
                            if($1->folder != NULL) {

                                // Quad to index the array
                                emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);  
                                $1->loc = t;

                                // Set type of unary_expression as type of indexed element
                                $1->type = tp.nextType;
                                $$ = $1;
                            }
                            else
                                $$ = $1;       
                        }
                        else
                            $$ = $1;           
                    }
                    | multiplicative_expression '*' unary_expression
                    {   
                    
                        $$ = new Expression();

                        // Get the Sym table entries of both computed Expression and new unary
                        // Expression
                        Sym* one = ST->Lookup($1->loc);                 
                        Sym* two = ST->Lookup($3->loc);   

                        // Handle case where unary_expression is of an ARRAY
                        if(two->type.type == ARRAY) {
                            string t = ST->GenerateTemp(two->type.nextType);

                            // Quad for indexing
                            emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                            $3->loc = t;

                            // Set type of unary_expression as type of indexed element
                            $3->type = two->type.nextType;
                        }
                        // Handle case where mult_expression is of an ARRAY
                        if(one->type.type == ARRAY) {                      
                            string t = ST->GenerateTemp(one->type.nextType);

                            // Quad for indexing
                            emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                            $1->loc = t;

                            // Set type of mult_expression as type of indexed element
                            $1->type = one->type.nextType;
                        }

                        // Set the resulting datatype
                        DataType final = ((one->type.type > two->type.type) ? (one->type.type) : (two->type.type));
                        $$->loc = ST->GenerateTemp(final);   

                        // Do the actual multiplication
                        // Emit Quad to multiply      
                        emit($$->loc, $1->loc, $3->loc, MULT);
                    }
                    | multiplicative_expression '/' unary_expression
                    {
                        
                        $$ = new Expression();

                        // Get the Sym table entries of both computed Expression and new unary
                        // Expression
                        Sym* one = ST->Lookup($1->loc);                 
                        Sym* two = ST->Lookup($3->loc);

                        // Handle case where unary_expression is of an ARRAY            
                        if(two->type.type == ARRAY) {                      
                            string t = ST->GenerateTemp(two->type.nextType);

                            // Quad for indexing
                            emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                            $3->loc = t;

                            // Set type of unary_expression as type of indexed element
                            $3->type = two->type.nextType;
                        }
                        // Handle case where mult_expression is of an ARRAY     
                        if(one->type.type == ARRAY) {                      
                            string t = ST->GenerateTemp(one->type.nextType);

                            // Quad for indexing
                            emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                            $1->loc = t;

                            // Set type of mult_expression as type of indexed element
                            $1->type = one->type.nextType;
                        }

                        // Set the resulting datatype
                        DataType final = ((one->type.type > two->type.type) ? (one->type.type) : (two->type.type));
                        $$->loc = ST->GenerateTemp(final);           

                        // Do the actual division
                        // Emit Quad to divide             
                        emit($$->loc, $1->loc, $3->loc, DIV);
                    }
                    | multiplicative_expression '%' unary_expression
                    {
                    
                        $$ = new Expression();

                        // Get the Sym table entries of both computed Expression and new unary
                        // Expression
                        Sym* one = ST->Lookup($1->loc);                 
                        Sym* two = ST->Lookup($3->loc);       

                        // Handle case where unary_expression is of an ARRAY           
                        if(two->type.type == ARRAY) {                      
                            string t = ST->GenerateTemp(two->type.nextType);

                            // Quad for indexing
                            emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                            $3->loc = t;

                            // Set type of unary_expression as type of indexed element
                            $3->type = two->type.nextType;
                        }
                        // Handle case where mult_expression is of an ARRAY 
                        if(one->type.type == ARRAY) {                      
                            string t = ST->GenerateTemp(one->type.nextType);

                            // Quad for indexing
                            emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                            $1->loc = t;

                            // Set type of mult_expression as type of indexed element
                            $1->type = one->type.nextType;
                        }

                        // Set the resulting datatype
                        DataType final = ((one->type.type > two->type.type) ? (one->type.type) : (two->type.type));
                        $$->loc = ST->GenerateTemp(final);   

                        // Do the actual modulo
                        // Emit Quad to modulo                    
                        emit($$->loc, $1->loc, $3->loc, MOD);
                    }
                    ;

/* 
    Additive expressions build on multiplicative expressions
 */
additive_expression: 
                multiplicative_expression {}
                | additive_expression '+' multiplicative_expression
                {   
                
                    $$ = new Expression();

                    // Get the Sym table entries of both computed Expression and new multiplicative
                    // Expression
                    Sym* one = ST->Lookup($1->loc);                 
                    Sym* two = ST->Lookup($3->loc);

                    // Handle case where mult_expression is of an ARRAY 
                    if(two->type.type == ARRAY) {                      
                        string t = ST->GenerateTemp(two->type.nextType);

                        // Quad for indexing
                        emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                        $3->loc = t;

                        // Set type of mult_expression as type of indexed element
                        $3->type = two->type.nextType;
                    }
                    // Handle case where additive_expression is of an ARRAY 
                    if(one->type.type == ARRAY) {                      
                        string t = ST->GenerateTemp(one->type.nextType);

                        // Quad for indexing
                        emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                        $1->loc = t;

                        // Set type of additive_expression as type of indexed element
                        $1->type = one->type.nextType;
                    }

                    // Set the resulting datatype
                    DataType final = ((one->type.type > two->type.type) ? (one->type.type) : (two->type.type));
                    $$->loc = ST->GenerateTemp(final);

                    // Do the actual addition
                    // Emit Quad to add                         
                    emit($$->loc, $1->loc, $3->loc, ADD);
                }
                | additive_expression '-' multiplicative_expression
                {
                    // Get the Sym table entries of both computed Expression and new multiplicative
                    // Expression
                    $$ = new Expression();
                    Sym* one = ST->Lookup($1->loc);                 
                    Sym* two = ST->Lookup($3->loc);         

                    // Handle case where unary_expression is of an ARRAY         
                    if(two->type.type == ARRAY) {                      
                        string t = ST->GenerateTemp(two->type.nextType);

                        // Quad for indexing
                        emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                        $3->loc = t;

                        // Set type of unary_expression as type of indexed element
                        $3->type = two->type.nextType;
                    }
                    // Handle case where unary_expression is of an ARRAY 
                    if(one->type.type == ARRAY) {                      
                        string t = ST->GenerateTemp(one->type.nextType);

                        // Quad for indexing
                        emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                        $1->loc = t;

                        // Set type of mult_expression as type of indexed element
                        $1->type = one->type.nextType;
                    }

                    // Set the resulting datatype
                    DataType final = ((one->type.type > two->type.type) ? (one->type.type) : (two->type.type));
                    $$->loc = ST->GenerateTemp(final);                      
                    
                    // Do the actual subtraction
                    // Emit Quad to subtract   
                    emit($$->loc, $1->loc, $3->loc, SUB);
                }
                ;

/* 
    Relational expressions build on additive expressions
 */
relational_expression: 
                    additive_expression {}
                    | relational_expression '<' additive_expression
                    {
                        $$ = new Expression();

                        // Get the Sym table entries of both computed Expression and new 
                        // Expression
                        Sym* one = ST->Lookup($1->loc);                 
                        Sym* two = ST->Lookup($3->loc); 

                        // Handle case where type is of ARRAY                
                        if(two->type.type == ARRAY) {                      
                            string t = ST->GenerateTemp(two->type.nextType);
                            emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                            $3->loc = t;
                            $3->type = two->type.nextType;
                        }
                        // Handle case where type is of ARRAY
                        if(one->type.type == ARRAY) {                      
                            string t = ST->GenerateTemp(one->type.nextType);
                            emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                            $1->loc = t;
                            $1->type = one->type.nextType;
                        }

                        $$ = new Expression();

                        // Gen new temp
                        $$->loc = ST->GenerateTemp();

                        // Assign type bool to exp
                        $$->type = BOOL;

                        // Backpatching related
                        emit($$->loc, "1", "", ASSIGN);
                        $$->truelist = makelist(nextinstr);

                        emit("", $1->loc, $3->loc, GOTO_LT);
                        emit($$->loc, "0", "", ASSIGN);

                        $$->falselist = makelist(nextinstr);
                        emit("", "", "", GOTO);                            
                    }
                    | relational_expression '>' additive_expression
                    {
                        $$ = new Expression();

                        // Get the Sym table entries of both computed Expression and new 
                        // Expression
                        Sym* one = ST->Lookup($1->loc);                 
                        Sym* two = ST->Lookup($3->loc); 

                        // Handle case where type is of ARRAY                
                        if(two->type.type == ARRAY) {                      
                            string t = ST->GenerateTemp(two->type.nextType);
                            emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                            $3->loc = t;
                            $3->type = two->type.nextType;
                        }
                        // Handle case where type is of ARRAY
                        if(one->type.type == ARRAY) {                      
                            string t = ST->GenerateTemp(one->type.nextType);
                            emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                            $1->loc = t;
                            $1->type = one->type.nextType;
                        }

                        $$ = new Expression();

                        // Gen new temp
                        $$->loc = ST->GenerateTemp();

                        // Assign type bool to exp
                        $$->type = BOOL;

                        // Backpatching related
                        emit($$->loc, "1", "", ASSIGN);
                        $$->truelist = makelist(nextinstr);   

                        emit("", $1->loc, $3->loc, GOTO_GT);               
                        emit($$->loc, "0", "", ASSIGN);

                        $$->falselist = makelist(nextinstr);               
                        emit("", "", "", GOTO);                            
                    }
                    | relational_expression LESS_THAN_EQUAL additive_expression
                    {
                        $$ = new Expression();

                        // Get the Sym table entries of both computed Expression and new 
                        // Expression
                        Sym* one = ST->Lookup($1->loc);                 
                        Sym* two = ST->Lookup($3->loc);

                        // Handle case where type is of ARRAY     
                        if(two->type.type == ARRAY) {                      
                            string t = ST->GenerateTemp(two->type.nextType);
                            emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                            $3->loc = t;
                            $3->type = two->type.nextType;
                        }
                        // Handle case where type is of ARRAY     
                        if(one->type.type == ARRAY) {                      
                            string t = ST->GenerateTemp(one->type.nextType);
                            emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                            $1->loc = t;
                            $1->type = one->type.nextType;
                        }
                        $$ = new Expression();

                        // Gen new temp
                        $$->loc = ST->GenerateTemp();

                        // Assign type bool to exp
                        $$->type = BOOL;           

                        // Backpatching related
                        emit($$->loc, "1", "", ASSIGN);
                        $$->truelist = makelist(nextinstr); 

                        emit("", $1->loc, $3->loc, GOTO_LTE);              
                        emit($$->loc, "0", "", ASSIGN);

                        $$->falselist = makelist(nextinstr);               
                        emit("", "", "", GOTO);                            
                    }
                    | relational_expression GREATER_THAN_EQUAL additive_expression
                    {
                        $$ = new Expression();

                        // Get the Sym table entries of both computed Expression and new 
                        // Expression
                        Sym* one = ST->Lookup($1->loc);                 
                        Sym* two = ST->Lookup($3->loc);    
                        
                        // Handle case where type is of ARRAY  
                        if(two->type.type == ARRAY)
                        {                      
                            string t = ST->GenerateTemp(two->type.nextType);
                            emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                            $3->loc = t;
                            $3->type = two->type.nextType;
                        }
                        // Handle case where type is of ARRAY  
                        if(one->type.type == ARRAY)
                        {                      
                            string t = ST->GenerateTemp(one->type.nextType);
                            emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                            $1->loc = t;
                            $1->type = one->type.nextType;
                        }
                        $$ = new Expression();

                        $$->loc = ST->GenerateTemp();

                        // Assign type bool to exp
                        $$->type = BOOL;        

                        // Backpatching related
                        emit($$->loc, "1", "", ASSIGN);
                        $$->truelist = makelist(nextinstr);

                        emit("", $1->loc, $3->loc, GOTO_GTE);              
                        emit($$->loc, "0", "", ASSIGN);

                        $$->falselist = makelist(nextinstr);               
                        emit("", "", "", GOTO);                            
                    }
                    ;

/* 
    Equality expressions build on relative expressions
 */
equality_expression: 
                relational_expression
                {
                    $$ = new Expression();
                    $$ = $1;               
                }
                | equality_expression EQUAL relational_expression
                {
                    $$ = new Expression();

                    Sym* one = ST->Lookup($1->loc);                 
                    Sym* two = ST->Lookup($3->loc);   

                    if(two->type.type == ARRAY)
                    {                      
                        string t = ST->GenerateTemp(two->type.nextType);
                        emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                        $3->loc = t;
                        $3->type = two->type.nextType;
                    }
                    if(one->type.type == ARRAY)
                    {                      
                        string t = ST->GenerateTemp(one->type.nextType);
                        emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                        $1->loc = t;
                        $1->type = one->type.nextType;
                    }

                    $$ = new Expression();

                    $$->loc = ST->GenerateTemp();

                    $$->type = BOOL;                                   
                    emit($$->loc, "1", "", ASSIGN);

                    $$->truelist = makelist(nextinstr);                
                    emit("", $1->loc, $3->loc, GOTO_EQ);               
                    emit($$->loc, "0", "", ASSIGN);

                    $$->falselist = makelist(nextinstr);               
                    emit("", "", "", GOTO);                            
                }
                | equality_expression NOT_EQUAL relational_expression
                {
                    $$ = new Expression();

                    Sym* one = ST->Lookup($1->loc);                 
                    Sym* two = ST->Lookup($3->loc);    

                    if(two->type.type == ARRAY)
                    {
                        string t = ST->GenerateTemp(two->type.nextType);
                        emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                        $3->loc = t;
                        $3->type = two->type.nextType;
                    }
                    if(one->type.type == ARRAY)
                    {
                        string t = ST->GenerateTemp(one->type.nextType);
                        emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                        $1->loc = t;
                        $1->type = one->type.nextType;
                    }

                    $$ = new Expression();

                    $$->loc = ST->GenerateTemp();

                    $$->type = BOOL;         

                    emit($$->loc, "1", "", ASSIGN);
                    $$->truelist = makelist(nextinstr);      

                    emit("", $1->loc, $3->loc, GOTO_NEQ);              
                    emit($$->loc, "0", "", ASSIGN);

                    $$->falselist = makelist(nextinstr);               
                    emit("", "", "", GOTO);                            
                }
                ;

/* 
    We use augumented rules with M to help with backpatching
 */
logical_and_expression: 
        equality_expression { }
        | logical_and_expression LOGICAL_AND M equality_expression
        {   
            // Backpatch
            backpatch($1->truelist, $3->instr);  

            // Merge
            $$->falselist = merge($1->falselist, $4->falselist);   

            $$->truelist = $4->truelist;

            // Set type as BOOl                           
            $$->type = BOOL;                                       
        }
        ;

/* 
    We use augumented rules with M to help with backpatching
 */
logical_or_expression: 
        logical_and_expression
        {}
        | logical_or_expression LOGICAL_OR M logical_and_expression
        {   
            // Backpatch
            backpatch($1->falselist, $3->instr);   

            // Merge                
            $$->truelist = merge($1->truelist, $4->truelist);

            $$->falselist = $4->falselist;

            // Set type as BOOl
            $$->type = BOOL;                                       
        }
        ;

/* We use augumented rules with M and N to help with backpatching */
conditional_expression: 
        logical_or_expression
        {
            $$ = $1;   
        }
        | logical_or_expression N '?' M Expression N ':' M conditional_expression
        {   

            list<int> temp = makelist(nextinstr);

            Sym* one = ST->Lookup($5->loc);

            // Create a temporary for the Expression
            $$->loc = ST->GenerateTemp(one->type.type);     
            $$->type = one->type.type;

            // Assign the conditional Expression
            emit($$->loc, $9->loc, "", ASSIGN);        

            // Prevent fall-through
            emit("", "", "", GOTO);

            // Backpatch with nextinstr
            backpatch($6->nextlist, nextinstr);        
            emit($$->loc, $5->loc, "", ASSIGN);

            temp = merge(temp, makelist(nextinstr));

            // Prevent fall-through
            emit("", "", "", GOTO);                    
            backpatch($2->nextlist, nextinstr);     

            // Convert the Expression to boolean
            IntToBool($1);

            // When $1 is true, control goes to $4 (Expression)
            backpatch($1->truelist, $4->instr);      
            
            // When $1 is false, control goes to $8 (conditional_expression)  
            backpatch($1->falselist, $8->instr);

            // Backpatch with nextinstr
            backpatch($2->nextlist, nextinstr);        
        }
        ;

assignment_operator: 
        '='
        {}
        ;

assignment_expression: 
        conditional_expression
        {}
        | unary_expression assignment_operator assignment_expression
        {   
            // Get the first operand from the Sym table
            Sym* sym1 = ST->Lookup($1->loc);   
            // Get the second operand from the Sym table     
            Sym* sym2 = ST->Lookup($3->loc);        

            // Check for array case
            if($1->fold == 0) {
                if(sym1->type.type != ARRAY)
                    emit($1->loc, $3->loc, "", ASSIGN);
                else
                    emit($1->loc, $3->loc, *($1->folder), ARR_IDX_RES);
            }
            else
                emit(*($1->folder), $3->loc, "", L_DEREF);

            // Do assignment
            $$ = $1;       
        }
        ;



Expression: 
        assignment_expression
        {}
        ;


Declaration: 
        type_specifier init_declarator_list ';'
        {
            DataType currType = $1;
            int currSize = -1;


            // This assigns correct size for the data type
            if(currType == INT)
                currSize = __INTEGER_SIZE;
            else if(currType == CHAR)
                currSize = __CHARACTER_SIZE;

            vector<Declaration*> decs = *($2);
            for(vector<Declaration*>::iterator it = decs.begin(); it != decs.end(); it++)
            {
                Declaration* currDec = *it;
                if(currDec->type == FUNCTION)
                {
                    ST = &globalST;
                    emit(currDec->name, "", "", FUNC_END);

                    Sym* one = ST->Lookup(currDec->name);       
                    Sym* two = one->nestedTable->Lookup("RETVAL", currType, currDec->pointers);

                    one->size = 0;
                    one->initVal = NULL;
                    continue;
                }

                Sym* three = ST->Lookup(currDec->name, currType);       
                three->nestedTable = NULL;
                if(currDec->li == vector<int>() && currDec->pointers == 0)
                {
                    three->type.type = currType;
                    three->size = currSize;

                    if(currDec->initVal != NULL)
                    {
                        string rval = currDec->initVal->loc;
                        emit(three->name, rval, "", ASSIGN);
                        three->initVal = ST->Lookup(rval)->initVal;
                    }
                    else
                        three->initVal = NULL;
                }
                else if(currDec->li != vector<int>())
                {        
                    three->type.type = ARRAY;
                    three->type.nextType = currType;
                    three->type.dims = currDec->li;

                    vector<int> temp = three->type.dims;
                    int sz = currSize;
                    for(int i = 0; i < (int)temp.size(); i++)
                        sz *= temp[i];

                    ST->offset += sz;
                    three->size = sz;
                    ST->offset -= 4;
                }
                else if(currDec->pointers != 0)
                {              
                    three->type.type = POINTER;
                    three->type.nextType = currType;
                    three->type.pointers = currDec->pointers;
                    ST->offset += (__POINTER_SIZE - currSize);
                    three->size = __POINTER_SIZE;
                }
            }
        }
        ;

init_declarator_list: 
        init_declarator
        {   
            // Create a vector of declarations and add push_back $1 to it
            $$ = new vector<Declaration*>;     
            $$->push_back($1);
        }
        ;

init_declarator: 
        declarator
        {
            $$ = $1;
            // Initialize the initVal to NULL as no initialization is done
            $$->initVal = NULL;        
        }
        | declarator '=' initializer
        {   
            $$ = $1;

            // Initialize the initVal to the value in $3
            $$->initVal = $3;          
        }
        ;

type_specifier: 
        VOID_
        {
            $$ = VOID;
        }
        | CHAR_
        {
            $$ = CHAR;
        }
        | INT_
        {
            $$ = INT; 
        }
        ;

declarator: 
        pointer direct_declarator
        {
            $$ = $2;
            $$->pointers = $1;
        }
        | direct_declarator
        {
            $$ = $1;
            $$->pointers = 0;
        }
        ;

direct_declarator: 
        IDENTIFIER
        {
            $$ = new Declaration();
            $$->name = *($1);
        }
        | '(' declarator ')'
        {}
        | direct_declarator '[' ']'
        {   
            // Array type
            $1->type = ARRAY;

            // Array of ints  
            $1->nextType = INT;    

            $$ = $1;
            $$->li.push_back(0);
        }
        | direct_declarator '[' assignment_expression ']'
        {
            // Array type
            $1->type = ARRAY;

            // Array of ints  
            $1->nextType = INT;   
            $$ = $1;
            int index = ST->Lookup($3->loc)->initVal->i;
            $$->li.push_back(index);
        }
        | direct_declarator '(' parameter_type_list_opt ')'
        {
            $$ = $1;

            // Of type function
            $$->type = FUNCTION;

            Sym* funcData = ST->Lookup($$->name, $$->type);
            SymTab* funcTable = new SymTab();
            funcData->nestedTable = funcTable;

            // Get the parameter list
            vector<param*> paramList = *($3);  

            for(int i = 0; i < (int)paramList.size(); i++)
            {
                param* curParam = paramList[i];

                // If the parameter is an array
                if(curParam->type.type == ARRAY)
                {         
                    funcTable->Lookup(curParam->name, curParam->type.type);
                    funcTable->Lookup(curParam->name)->type.nextType = INT;
                    funcTable->Lookup(curParam->name)->type.dims.push_back(0);
                }
                // If the parameter is a pointer
                else if(curParam->type.type == POINTER)
                {  
                    funcTable->Lookup(curParam->name, curParam->type.type);
                    funcTable->Lookup(curParam->name)->type.nextType = INT;
                    funcTable->Lookup(curParam->name)->type.dims.push_back(0);
                }
                // If the parameter is a anything other than an array or a pointer
                else                                       
                    funcTable->Lookup(curParam->name, curParam->type.type);
            }

            // Set the pointer to the Sym table to the function's Sym table
            ST = funcTable;
            emit($$->name, "", "", FUNC_BEG);
        }
        ;

/* A pointer rule */
pointer: 
    '*'
    {
        $$ = 1;
    }
    ;


parameter_list: 
        parameter_declaration
        {   
            // Create a new vector of parameters
            $$ = new vector<param*>;

            // Add the parameter to the vector
            $$->push_back($1);             
        }
        | parameter_list ',' parameter_declaration
        {   
            // Add the parameter to the vector
            $1->push_back($3);             
            $$ = $1;
        }
        ;

parameter_type_list_opt:
        parameter_list
        {}
        | %empty
        {
            $$ = new vector<param*>;
        }
        ;

parameter_declaration: 
        type_specifier declarator
        {
            $$ = new param();
            $$->name = $2->name;

            if($2->type == ARRAY)
            {
                $$->type.type = ARRAY;
                $$->type.nextType = $1;
            }
            else if($2->pc != 0)
            {
                $$->type.type = POINTER;
                $$->type.nextType = $1;
            }
            else
                $$->type.type = $1;
        }
        | type_specifier
        {}
        ;

/* Initializer */
initializer: 
        assignment_expression
        {   
            // Just a simple assignment
            $$ = $1;
        }
        ;

/* The different types of statements */
statement: 
        compound_statement
        | expression_statement
        | selection_statement
        | iteration_statement
        | jump_statement
        ;

/* 
    Used for combining multiple statements into one
 */
compound_statement: 
        '{' '}'
        {}
        | '{' block_item_list '}'
        {
            $$ = $2;
        }
        ;

block_item_list: 
        block_item
        {   
            // Just a simple assignment
            $$ = $1;
            backpatch($1->nextlist, nextinstr);
        }
        | block_item_list M block_item
        {   
            $$ = new Expression();

            // After $1, move to block_item via $2
            backpatch($1->nextlist, $2->instr);   
            $$->nextlist = $3->nextlist;
        }
        ;

block_item: 
        Declaration
        {
            $$ = new Expression();  
        }
        | statement
        ;

expression_statement: 
        Expression ';'
        {}
        | ';'
        {
            $$ = new Expression(); 
        }
        ;

selection_statement: 
        IF '(' Expression N ')' M statement N
        {   
            // This is for only IF
            backpatch($4->nextlist, nextinstr);        
            IntToBool($3);                      
            backpatch($3->truelist, $6->instr);        
            $$ = new Expression();                     
        
            $7->nextlist = merge($8->nextlist, $7->nextlist);
            $$->nextlist = merge($3->falselist, $7->nextlist);
        }
        | IF '(' Expression N ')' M statement N ELSE M statement N
        {   
            // This is for IF and ELSE

            // nextlist of N now has nextinstr
            backpatch($4->nextlist, nextinstr);        

            // Convert Expression to bool
            IntToBool($3);

            // Backpatching - if Expression is true, go to first M, else go to second M     
            backpatch($3->truelist, $6->instr);        
            backpatch($3->falselist, $10->instr);
            $$ = new Expression();                     
        
            $$->nextlist = merge($7->nextlist, $8->nextlist);
            $$->nextlist = merge($$->nextlist, $11->nextlist);
            $$->nextlist = merge($$->nextlist, $12->nextlist);
        }
        ;

iteration_statement: 
        FOR '(' expression_statement M expression_statement N M Expression N ')' M statement
        {
            $$ = new Expression();                  
            emit("", "", "", GOTO);
            $12->nextlist = merge($12->nextlist, makelist(nextinstr - 1));
            backpatch($12->nextlist, $7->instr);   
            backpatch($9->nextlist, $4->instr);     
            backpatch($6->nextlist, nextinstr);     
            IntToBool($5);                  
            backpatch($5->truelist, $11->instr);   
            $$->nextlist = $5->falselist;          
        }
        ;

jump_statement: 
        RETURN_ ';'
        {
            if(ST->Lookup("RETVAL")->type.type == VOID) {
                emit("", "", "", RETURN);          
            }
            $$ = new Expression();
        }
        | RETURN_ Expression ';'
        {
            if(ST->Lookup("RETVAL")->type.type == ST->Lookup($2->loc)->type.type) {
                emit($2->loc, "", "", RETURN);     
            }
            $$ = new Expression();
        }
        ;

translation_unit: 
        external_declaration
        {}
        | translation_unit external_declaration
        {}
        ;

external_declaration: 
        function_definition
        {}
        | Declaration
        {}
        ;

function_definition: 
        type_specifier declarator declaration_list compound_statement
        {}
        | function_prototype compound_statement
        {
            ST = &globalST;                    
            emit($1->name, "", "", FUNC_END);
        }
        ;

function_prototype:
        type_specifier declarator
        {
            DataType currType = $1;
            int currSize = -1;
            if(currType == CHAR)
                currSize = __CHARACTER_SIZE;
            if(currType == INT)
                currSize = __INTEGER_SIZE;

            Declaration* currDec = $2;
            Sym* sym = globalST.Lookup(currDec->name);
            if(currDec->type == FUNCTION)
            {
                Sym* retval = sym->nestedTable->Lookup("RETVAL", currType, currDec->pointers);  
                sym->size = 0;
                sym->initVal = NULL;
            }
            $$ = $2;
        }
        ;

declaration_list: 
        Declaration
        {}
        | declaration_list Declaration
        {}
        ;

%%

/* 
    implementation of yyerror used to output error messages
 */
void yyerror(string s) {
    cout << s << "at line no: " << yylineno << " : " << yytext << endl;
}


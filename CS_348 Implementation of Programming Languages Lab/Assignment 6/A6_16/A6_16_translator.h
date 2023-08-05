#ifndef __TRANSLATOR_H
#define __TRANSLATOR_H

#include <bits/stdc++.h>
using namespace std;

// Size definitions
#define __VOID_SIZE 0
#define __FUNCTION_SIZE 0
#define __CHARACTER_SIZE 1
#define __INTEGER_SIZE 4
#define __POINTER_SIZE 8

// An enum for all data types
typedef enum {
    VOID,
    BOOL,
    CHAR,
    INT,
    ARRAY,
    POINTER,
    FUNCTION
} DataType;

// An enum for all opcodes
typedef enum  {
    ADD,
    SUB,
    MULT,
    DIV, 
    MOD, 
    SL, 
    SR, 
    U_PLUS,
    U_MINUS, 
    REFERENCE, 
    DEREFERENCE, 
    LOG_NOT, 
    GOTO_EQ, 
    GOTO_NEQ, 
    GOTO_GT, 
    GOTO_GTE, 
    GOTO_LT, 
    GOTO_LTE, 
    IF_GOTO, 
    IF_FALSE_GOTO, 
    CtoI, 
    ItoC, 
    ASSIGN, 
    GOTO, 
    RETURN, 
    PARAM, 
    CALL, 
    ARR_IDX_ARG,
    ARR_IDX_RES, 
    FUNC_BEG, 
    FUNC_END, 
    L_DEREF
} opcode;

// Classes
class Sym;       // Represents an element(entry) in the Sym table
class SymType;   // Represents the type of an element in the Sym table
class SymVal;  // Represents the value stored by a Sym in the Sym table
class SymTab;  // Represents the Sym table data structure itself
class Quad;         // Denotes a Quad in the Three Address Code translation
class QuadArr;    // Denotes the entire list of quads for lazy spitting

// External variables and methods
extern char* yytext;
extern int yyparse();

//////////////////////////
//  CLASS DEFINITIONS   //
/////////////////////////

// Class to represent the type of an element in the Sym table
class SymType {
public:
    vector<int> dims;   // For arrays, it stores the dimensions of the array
    int pointers;       // Useful for pointer types
    DataType type;      // The type of the Sym
    DataType nextType;  // For arrays and pointers, it points to the type of the elements of the array or the pointer
};

// Class to represent an element(entry) in the Sym table
class Sym {
public:
    int size;                   // Size of the Sym(element)
    int offset;                 // Offset of the Sym in the Sym table
    SymVal* initVal;       // Initial value of the Sym

    SymType type;            // Type of the Sym
    string name;                // The name of the Sym
    SymTab* nestedTable;   // Pointer to a nested Sym table

    // Methods
    Sym();                   // Contructor
};

// Class to represent the value of an element in the Sym table
class SymVal {
public:
    void* p;                    // For pointers
    int i;                      // For integers
    char c;                     // For characters

    // Methods
    void SetInit(int val);   // To Set Value
    void SetInit(char val);  // To Set Value
};



// Class to represent the Sym table data structure
class SymTab {
public:
    int offset;
    static int tempCount;                                       // Count of temporary variables generated for the Sym table
    map<string, Sym*> table;                                 // List of symbols hashed using their names
    vector<Sym*> symbols;                                    // List of all symbols present in the Sym table
    
    // Methods
    void print(string tableName);                               // Prints the Sym table
    Sym* Lookup(string name, DataType t = INT, int pc = 0);  // A method to Lookup an id (given its name or lexeme) in the Sym table
    Sym* SearchGlob(string name);                          // A method to search for an id in the global Sym table
    string GenerateTemp(DataType t = INT);                           // A method to generate a new temporary and insert it to the Sym table
    SymTab();                                              // Constructor
};


// Class to denote a Quad in the Three Address Code translation
class Quad {
public:
    string arg1;                            // First argument in the three address code
    string arg2;                            // Second argument in the three address code
    opcode op;                              // Operator in the three address code
    string result;                          // Result of the three address code

    // Methods
    string print();                         // Returns a formatted string to help in printing the Quad

    Quad(string, string, string, opcode);   // Constructor
}; 

// Class to denote the entire list of quads for lazy spitting
class QuadArr {
public:
    vector<Quad> quads; // A vector of all the quads generated

    // Methods
    void print();       // Prints the entire list of quads
};

// Class to represent a parameter
class param {
public:
    SymType type;    // Type of parameter
    string name;        // Name of parameter
};

// Class to denote an Expression
class Expression {
public:
    int instr;              // The instruction number of the Expression
    DataType type;          // Type of the Expression
    string loc;             // The Sym table entry
    
    // folder stuff
    int fold;               // Useful for arrays and pointers
    string* folder;         // Useful for arrays and pointers

    list<int> truelist;     // Truelist for boolean expressions
    list<int> falselist;    // Falselist for boolean expressions
    list<int> nextlist;     // Nextlist for statement expressions

    // Methods
    Expression();           // Constructor
};

// Class to represent a Declaration
class Declaration {
public:
    int pointers;           // Number of pointers
    int pc;                 // Useful for pointers and arrays
    string name;            // Name of the Declaration
    Expression* initVal;    // Initial value of the Declaration
    DataType type;          // Type of the Declaration
    DataType nextType;
    vector<int> li;         // List of instructions for the Declaration
};




//////////////////////////////
//  Function DEFINITIONS   //
////////////////////////////

// An overloaded method to add a (newly generated) Quad of the form: result = arg1 op arg2, where op usually is a binary operator. 
// If arg2 is missing, op is unary. If op also is missing, this is a copy instruction.
// It is overloaded for different types of quads (int string)
void emit(string result, string arg1, string arg2, opcode op);
void emit(string result, int constant, opcode op);
void emit(string result, char constant, opcode op);

// A global function to create a new list containing only i, an index into the array of quads, 
// Returns a pointer to the newly created list
list<int> makelist(int i);

// A global function to concatenate two lists list1 and list2 and to return a pointer to the concatenated list
list<int> merge(list<int> list1, list<int> list2);

// A global function to insert address as the target label for each of the quads on the list l
void backpatch(list<int> l, int address);

// Converts a Sym of one type to another and returns a pointer to the converted Sym
void ConvertTo(Expression* arg, Expression* res, DataType toType);
void ConvertTo(string t, DataType to, string f, DataType from);

// Converts an int to a bool and adds required attributes
void IntToBool(Expression* expr);

// Auxiliary function to get the size of a type
int TypeSize(DataType t);

// Auxiliary function to print a type
string TypeCheck(SymType t);

// Auxiliary function to get the initial value of a Sym
string GetInit(Sym* sym);


#endif
NAME :: Akshat Mittal
ROLL NUMBER :: 200101011

--------------------------------------------------

DETAILS FOR COMPILATION ::

Run the following command -
    g++ main.cpp    (Build)
    ./a.out         (Execute)

---------------------------------------------------

INPUT FILE FORMAT ::

* The input file must be called "input.txt"
* Comment lines should start with '.'
* No inline comments are allowed following instructions

* The instruction file must be called "optab.txt"
* Optab will be loaded from this file at start of program

----------------------------------------------------

OUTPUT FORMAT ::

Three output files are generated -
* intermediate.txt  : Intermediate file generated during pass 1 of the assembler, containing address of each instruction
* symtab.txt        : Contains the symbol table generated after pass 1.
* output.txt        : Contains the final object program in machine code.

----------------------------------------------------

SUBMITTED FILES ::

* main.cpp      : The code file containing the assembler 
* optab.txt     : File containing opcodes for each of the operations to be allowed
* input.txt     : Contains a sample input which can be used to check correctness
* Readme.txt    : Contains the readme for the project
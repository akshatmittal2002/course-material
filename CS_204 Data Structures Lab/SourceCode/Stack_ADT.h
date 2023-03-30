#ifndef STACK_ADT_H
#define STACK_ADT_H
#include "..\SourceCode\Array_ADT.h"

class Stack_ADT
{
    public:
        Stack_ADT() = delete;///This ensures that our default constructor is not been called, i.e., creation of stack is disabled without specifying capacity.
        Stack_ADT(int);
        bool IsEmpty();
        bool IsFull();
        bool push(int);
        int pop();
        virtual ~Stack_ADT();

        void print_stack();

    protected:

    private:
        int counter;
        Array_ADT members;
};

#endif // STACK_ADT_H
